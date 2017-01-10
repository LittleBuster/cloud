/*
 * Cloud: storage application
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */


#include <iostream>

#include <unistd.h>

#include "cloudstorage.h"
#include "filesender.h"
#include "filereceiver.h"
#include "network.h"
#include "session.h"


CloudStorage::CloudStorage(const shared_ptr<IConfigs> &cfg, const shared_ptr<ILog> &log, const shared_ptr<IUsersBase> &usersBase, const shared_ptr<IFilesBase> &filesBase):
                           cfg_(move(cfg)), log_(move(log)), usersBase_(move(usersBase)),
                           filesBase_(move(filesBase))
{
}

void CloudStorage::newSession(shared_ptr<ITcpClient> client)
{
    Command cmd;
    bool current = true;
    vector<File> downloadList;
    vector<string> uploadedList;
    auto session = make_shared<Session>(client, cfg_, usersBase_, mtx_);

    while (true) {
        try {
            client->recv(&cmd, sizeof(cmd));
        }
        catch (const string &err) {
             log_->local("Receiving command: " + err, LOG_ERROR);
            return;
        }

        switch (cmd.code) {
            case CMD_LOGIN: {
                try {
                    session->openNewSession();
                    if (session->getPrivilegies() == PV_ADMIN)
                        cout << "New client [ADMIN] connected." << endl;
                    else
                        cout << "New client [USER] connected." << endl;
                }
                catch (const string &err) {
                    mtx_.unlock();
                    log_->local("Checking user: " + err, LOG_ERROR);
                    return;
                }
                break;
            }
            case CMD_SEND_FILE: {
                FileInfo info;
                File file;
                Command answ;
                const auto &syc = cfg_->getSyncCfg();
                const auto &fbc = cfg_->getFilesBaseCfg();

                try {
                    client->recv(&info, sizeof(info));

                    file.filename = string(info.filename);
                    file.size = info.size;
                    file.modify = string(info.modify_time);
                    file.hash = string(info.hash);

                    uploadedList.push_back(file.filename);

                    mtx_.lock();
                    filesBase_->open(fbc.path);
                    if (filesBase_->exists(file)) {
                        if (filesBase_->verify(file)) {
                            filesBase_->close();
                            mtx_.unlock();

                            answ.code = ANSW_NOTHING;
                            client->send(&answ, sizeof(answ));
                            break;
                        }
                        else
                            cout << "File has depricated." << endl;
                    }
                    current = false;

                    filesBase_->close();
                    mtx_.unlock();

                    answ.code = ANSW_NEED_UPLOAD;
                    client->send(&answ, sizeof(answ));

                    // Show info
                    cout << "Receiving: " << file.filename << " " << file.size << " " << file.modify << endl;

                    // Receiving file from client
                    FileReceiver fr(syc.path + string(info.filename), info.size);
                    fr.download(client);

                    mtx_.lock();
                    filesBase_->open(fbc.path);
                    filesBase_->addFile(file);
                    filesBase_->close();
                    mtx_.unlock();                    
                }
                catch (const string &err) {
                    mtx_.unlock();
                    log_->local("Receiving file: " + err, LOG_ERROR);
                }                
                break;
            }

            case CMD_FILES_COUNT: {
                Command answ;
                const auto &fbc = cfg_->getFilesBaseCfg();

                try {
                    mtx_.lock();
                    filesBase_->open(fbc.path);
                    downloadList = filesBase_->getFileList();
                    filesBase_->close();
                    mtx_.unlock();
                } catch(const string &err) {
                    mtx_.unlock();
                    log_->local("Get file count: " + err, LOG_ERROR);
                    break;
                }

                try {
                    answ.code = downloadList.size();
                    client->send(&answ, sizeof(answ));
                } catch(const string &err) {
                    mtx_.unlock();
                    log_->local("Get file count: " + err, LOG_ERROR);
                }
                break;
            }

            case CMD_FILE_INFO: {
                FileInfo info;
                const auto &fbc = cfg_->getFilesBaseCfg();

                try {
                    if (downloadList.empty()) {
                        strcpy(info.filename, "");
                        info.size = 0;
                        client->send(&info, sizeof(info));
                        break;
                    }

                    const auto curFile = downloadList[downloadList.size()-1];

                    mtx_.lock();
                    filesBase_->open(fbc.path);
                    if (!filesBase_->exists(curFile)) {
                        strcpy(info.filename, "");
                        info.size = 0;
                    } else {
                        strncpy(info.filename, curFile.filename.c_str(), 254);
                        info.size = curFile.size;
                        strncpy(info.modify_time, curFile.modify.c_str(), 50);
                        strncpy(info.hash, curFile.hash.c_str(), 512);
                    }
                    filesBase_->close();
                    mtx_.unlock();

                    client->send(&info, sizeof(info));
                } catch(const string &err) {
                    mtx_.unlock();
                    log_->local("File info: " + err, LOG_ERROR);
                }
                break;
            }

            case CMD_RECV_FILE: {
                const auto &syc = cfg_->getSyncCfg();

                if (downloadList.empty()) {
                    log_->local("Files for downloading not found.", LOG_ERROR);
                    break;
                }
                const auto curFile = downloadList[downloadList.size()-1];

                try {
                    cout << "Sending file: " << curFile.filename << endl;

                    FileSender fs(syc.path + curFile.filename, curFile.size);
                    fs.upload(client);
                } catch(const string &err) {
                    log_->local("Receiving file: " + err, LOG_ERROR);
                }
                downloadList.pop_back();
                break;
            }

            case CMD_CLEAN: {
                cleanFiles(uploadedList);
                uploadedList.clear();
                break;
            }

            case CMD_EXIT: {
                if (current)
                    cout << "All files are current." << endl;

                if (session->getPrivilegies() == PV_ADMIN)
                    cout << "Client [ADMIN] disconnected." << endl;
                else
                    cout << "Client [USER] disconnected." << endl;
                session->close();
                return;
            }
        }
    }
}

void CloudStorage::acceptError() const
{
    log_->local("Accepting client error.", LOG_WARNING);
}

void CloudStorage::serverStarted() const
{
    cout << "Cloud server was started." << endl;
}

void CloudStorage::cleanFiles(const vector<string> &files)
{
    const auto &fbc = cfg_->getFilesBaseCfg();
    const auto &syc = cfg_->getSyncCfg();

    auto existsFile = [](const File &localFile, const vector<string> &uploadedFiles) {
        for (const auto &filename : uploadedFiles) {
            if (filename == localFile.filename) {
                return true;
            }
        }
        return false;
    };

    mtx_.lock();
    filesBase_->open(fbc.path);
    const auto localFiles = filesBase_->getFileList();

    for (const auto &file : localFiles) {
        if (!existsFile(file, files)) {
            string fullPath = syc.path + file.filename;
            filesBase_->removeFile(file);
            remove(fullPath.c_str());
        }
    }

    filesBase_->close();
    mtx_.unlock();
}
