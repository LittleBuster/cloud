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


#include <vector>
#include <ctime>
#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>

#include "filewatch.h"
#include "filehash.h"
#include "network.h"

namespace fs = boost::filesystem;


MasterWatch::MasterWatch(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg,
                     const shared_ptr<ITcpClient> &client, const shared_ptr<ISession> &session):
                     log_(move(log)), cfg_(move(cfg)), client_(move(client)), session_(move(session))
{
}

void MasterWatch::handler()
{
    Command cmd;
    vector<fs::path> files;
    const auto &syc = cfg_->getSyncCfg();

    try {
        copy(fs::directory_iterator(fs::path(syc.path)), fs::directory_iterator(), back_inserter(files));
        session_->openNewSession();
    }
    catch (const string &err) {
        log_->local("FileWatch: " + err, LOG_ERROR);
        return;
    }

    for (const fs::path &file : files) {
        FileInfo info;
        stringstream sstream;

        if (!fs::is_regular_file(file))
            continue;

        strncpy(info.filename, file.filename().string().c_str(), 255);
        info.size = fs::file_size(file);
        sstream << fs::last_write_time(file);
        strncpy(info.modify_time, sstream.str().c_str(), 50);

        try {
            cmd.code = CMD_SEND_FILE;
            client_->send(&cmd, sizeof(cmd));
            client_->send(&info, sizeof(info));

            // Receiving answ
            client_->recv(&cmd, sizeof(cmd));
            if (cmd.code == ANSW_NEED_UPLOAD) {
                FileSender fs(syc.path + file.filename().string(), info.size);
                fs.upload(client_);
            }
        }
        catch (const string &err) {
            log_->local(err, LOG_ERROR);
            continue;
        }
    }
    session_->close();
}
