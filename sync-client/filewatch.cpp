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
#include "ext.h"


FileWatch::FileWatch(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg,
                     const shared_ptr<ITcpClient> &client):
                     log_(move(log)), cfg_(move(cfg)), client_(move(client))
{
}

vector<File> FileWatch::GetFileList(const string &path)
{
    DIR *dir;
    vector<File> local_files;
    struct dirent *file_cur;

    if ((dir = opendir(path.c_str())) == NULL)
        throw string("Fail open path \"" + path + "\"");

    while ((file_cur = readdir(dir)) != NULL) {
        struct stat sbuf;
        File file;
        string full_path = path + "/";

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

void FileWatch::Handler()
{
    const auto &sc = cfg_->GetServerCfg();
    const auto &syc = cfg_->GetSyncCfg();
    vector<File> local_files;
    Command cmd;

    try {
        local_files = GetFileList(syc.path);
    }
    catch (const string &err) {
        log_->Local("FileWatch: " + err, LOG_ERROR);
        return;
    }

    try {
        client_->Connect(sc.ip, sc.port);
    }
    catch (const string &err) {
        log_->Local(err, LOG_ERROR);
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
            client_->Send(&cmd, sizeof(Command));
            client_->Send(&info, sizeof(FileInfo));

            FileSender fs(syc.path + file.name, file.size);
            fs.Upload(client_);
        }
        catch (const string &err) {
            log_->Local(err, LOG_ERROR);
            continue;
        }
    }

    try {
        cmd.code = CMD_EXIT;
        client_->Send(&cmd, sizeof(Command));
    }
    catch (const string &err) {
        log_->Local(err, LOG_ERROR);
    }

    client_->Close();
}
