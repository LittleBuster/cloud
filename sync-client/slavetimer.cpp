/*
 * Cloud: sync client application
 *
 * Copyright (C) 2016-2017 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#include <vector>
#include <ctime>
#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>

#include "filehash.h"
#include "network.h"
#include "slavetimer.h"
#include "filehash.h"

namespace fs = boost::filesystem;


SlaveTimer::SlaveTimer(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg,
                     const shared_ptr<ITcpClient> &client, const shared_ptr<ISession> &session):
                     log_(move(log)), cfg_(move(cfg)), client_(move(client)), session_(move(session))
{
    BOOST_ASSERT(log != nullptr);
    BOOST_ASSERT(cfg != nullptr);
    BOOST_ASSERT(client != nullptr);
    BOOST_ASSERT(session != nullptr);
}

void SlaveTimer::handler()
{
    Command cmd, answ;
    vector<fs::path> files;
    vector<string> transferedFiles;
    const auto &syc = cfg_->getSyncCfg();

    try {
        copy(fs::directory_iterator(fs::path(syc.path)), fs::directory_iterator(), back_inserter(files));
        session_->openNewSession();

        cmd.code = CMD_FILES_COUNT;
        client_->send(&cmd, sizeof(cmd));
        client_->recv(&answ, sizeof(answ));
    }
    catch (const string &err) {
        log_->local("FileWatch: " + err, LOG_ERROR);
        return;
    }

    for (size_t i = 0; i < answ.code; i++) {
        FileInfo info;

        try {
            cmd.code = CMD_FILE_INFO;
            client_->send(&cmd, sizeof(cmd));
            client_->recv(&info, sizeof(info));
        } catch(const string &err) {
            log_->local("Fail getting file info: " + err, LOG_ERROR);
            continue;
        }

        if (info.size == 0 && string(info.filename) == "") {
            cout << "File " << string(info.filename) << " already deleted." << endl;
            continue;
        }

        try {
            transferedFiles.push_back(string(info.filename));
            if (checkFile(info))
                continue;
        } catch(...) {
            log_->local("Fail checking local file.", LOG_ERROR);
            continue;
        }

        try {
            cout << "Downloading file: " << string(info.filename) << endl;

            cmd.code = CMD_RECV_FILE;
            client_->send(&cmd, sizeof(cmd));

            FileReceiver frecv(syc.path + string(info.filename), info.size);
            frecv.download(client_);
        } catch(const string &err) {
            log_->local("Fail downloading " + string(info.filename) + " : " + err, LOG_ERROR);
        }
    }
    session_->close();
    cout << "Disconnected." << endl;

    deleteFilesAsNeeded(transferedFiles);

    timer_->expires_at(timer_->expires_at() + boost::posix_time::seconds(delay_));
    timer_->async_wait(bind(&SlaveTimer::handler, this));
}

void SlaveTimer::start(unsigned delay)
{
    delay_ = delay;
    timer_ = make_shared<deadline_timer>(io_, boost::posix_time::seconds(delay_));
    timer_->async_wait(bind(&SlaveTimer::handler, this));
    io_.run();
}

void SlaveTimer::stop() const
{
    timer_->cancel();
}

bool SlaveTimer::checkFile(const FileInfo &info) const
{
    vector<fs::path> files;
    const auto &syc = cfg_->getSyncCfg();

    copy(fs::directory_iterator(fs::path(syc.path)), fs::directory_iterator(), back_inserter(files));
    for (const auto &file : files) {
        if (file.filename().string() == string(info.filename)) {
            FileHash hash(syc.path + string(info.filename));

            if (hash.generate() != string(info.hash))
                return false;
            if (fs::file_size(file) != info.size)
                return false;

            return true;
        }
    }
    return false;
}

void SlaveTimer::deleteFilesAsNeeded(const vector<string> &files)
{
    const auto &syc = cfg_->getSyncCfg();
    vector<fs::path> localFiles;

    copy(fs::directory_iterator(fs::path(syc.path)), fs::directory_iterator(), back_inserter(localFiles));

    auto fileExists = [](const string &filename, const vector<string> &files) {
        for (const auto &transferedFile : files) {
            if (filename == transferedFile) {
                return true;
            }
        }
        return false;
    };

    for (const auto &file : localFiles) {
        if (!fileExists(file.filename().string(), files)) {
            cout << "Deleting file: " << file.filename().string() << endl;
            fs::remove(file);
        }
    }
}
