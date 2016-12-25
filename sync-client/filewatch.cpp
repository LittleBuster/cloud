// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <vector>
#include <ctime>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include "filewatch.h"
#include "filehash.h"
#include "network.h"
#include "ext.h"


MasterWatch::MasterWatch(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg,
                     const shared_ptr<ITcpClient> &client, const shared_ptr<ISession> &session):
                     log_(move(log)), cfg_(move(cfg)), client_(move(client)), session_(move(session))
{
}

vector<File> MasterWatch::GetFileList(const string &path)
{
    DIR *dir;
    vector<File> local_files;
    struct dirent *file_cur;

    if ((dir = opendir(path.c_str())) == NULL)
        throw string("Fail open path \"" + path);

    while ((file_cur = readdir(dir)) != NULL) {
        struct stat sbuf;
        File file;
        string full_path = path;

        file.name = string(file_cur->d_name);
        full_path += file.name;

        /*
         * Ignoring hidden files and prev folders
         */
        if (file.name == "." || file.name == ".." || file.name[0] == '.')
            continue;

        /*
         * Is it a folder?
         */
        if (ext::pos(file.name, '.') == -1)
            continue;

        int fd = open(full_path.c_str(), O_RDONLY);
        if (fd == -1)
            continue;

        /*
         * Getting size and last modify date
         */
        fstat(fd, &sbuf);
        file.modify = ext::date_to_str(&sbuf.st_mtime);
        file.size = sbuf.st_size;
        close(fd);        

        /*
         * Generating hash of file
         */
        FileHash hash(full_path);
        file.hash = hash.Generate();

        local_files.push_back(file);
    }
    closedir(dir);
    return local_files;
}

void MasterWatch::Handler()
{
    const auto &syc = cfg_->GetSyncCfg();
    vector<File> local_files;
    Command cmd;

    try {
        local_files = GetFileList(syc.path);
        session_->OpenNewSession();
    }
    catch (const string &err) {
        log_->Local("FileWatch: " + err, LOG_ERROR);
        return;
    }

    for (const File &file : local_files) {
        FileInfo info;

        strncpy(info.filename, file.name.c_str(), 255);
        strncpy(info.hash, file.hash.c_str(), 512);
        strncpy(info.modify_time, file.modify.c_str(), 49);
        info.size = file.size;

        try {
            cmd.code = CMD_SEND_FILE;
            client_->Send(&cmd, sizeof(cmd));
            client_->Send(&info, sizeof(info));

            // Receiving answ
            client_->Recv(&cmd, sizeof(cmd));
            if (cmd.code == ANSW_NEED_UPLOAD) {
                FileSender fs(syc.path + file.name, file.size);
                fs.Upload(client_);
            }
        }
        catch (const string &err) {
            log_->Local(err, LOG_ERROR);
            continue;
        }
    }
    session_->CloseSession();
}
