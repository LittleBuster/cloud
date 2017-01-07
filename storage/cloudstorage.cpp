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

#include "cloudstorage.h"
#include "filetransfer.h"
#include "network.h"
#include "session.h"


CloudStorage::CloudStorage(const shared_ptr<IConfigs> &cfg, const shared_ptr<ILog> &log, const shared_ptr<IUsersBase> &users_base, const shared_ptr<IFilesBase> &files_base):
                           cfg_(move(cfg)), log_(move(log)), users_base_(move(users_base)),
                           files_base_(move(files_base))
{
}

void CloudStorage::newSession(shared_ptr<ITcpClient> client)
{
    Command cmd;
    bool current = true;
    auto session = make_shared<Session>(client, cfg_, users_base_, mtx_);

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

                    mtx_.lock();
                    files_base_->open(fbc.path);
                    if (files_base_->exists(file)) {
                        if (files_base_->verify(file)) {
                            files_base_->close();
                            mtx_.unlock();

                            answ.code = ANSW_NOTHING;
                            client->send(&answ, sizeof(answ));
                            break;
                        }
                        else
                            cout << "File has depricated." << endl;
                    }
                    else
                        cout << "File not found." << endl;
                    current = false;

                    files_base_->close();
                    mtx_.unlock();

                    answ.code = ANSW_NEED_UPLOAD;
                    client->send(&answ, sizeof(answ));

                    // Show info
                    cout << "Receiving: " << file.filename << " " << file.size << " " << file.modify << endl;

                    // Receiving file from client
                    FileReceiver fr(syc.path + string(info.filename), info.size);
                    fr.download(client);

                    mtx_.lock();
                    files_base_->open(fbc.path);
                    files_base_->addFile(file);
                    files_base_->close();
                    mtx_.unlock();
                }
                catch (const string &err) {
                    mtx_.unlock();
                    log_->local("Receiving file: " + err, LOG_ERROR);
                }                
                break;
            }

            case CMD_RECV_FILE: {
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
                break;
            }
        }
    }
}

void CloudStorage::acceptError() const
{

}

void CloudStorage::serverStarted() const
{

}
