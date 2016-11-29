/* Cloud: sync client application
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#include "filewatch.h"
#include "ext.h"
#include <vector>
#include <ctime>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <iostream>


FileWatch::FileWatch(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg,
                     const shared_ptr<IFileHash> &fhash, const shared_ptr<IFileTransfer> &ftransfer,
                     const shared_ptr<ITcpClient> &client):
                     _log(move(log)), _cfg(move(cfg)), _fhash(move(fhash)), _ftransfer(move(ftransfer)),
                     _client(move(client))
{
}

string FileWatch::dateToStr(time_t *time)
{
    char time_str[20];
    char date_str[20];
    struct tm *timeinfo;
    string out;

    timeinfo = localtime(time);
    strftime(date_str, 20, "%F", timeinfo);
    strftime(time_str, 20, "%T", timeinfo);

    out = string(date_str) + " " + string(time_str);
    return out;
}

vector<File> FileWatch::getFileList(const string &path)
{
    DIR *dir;
    vector<File> localFiles;
    struct dirent *f_cur;

    if ((dir = opendir(path.c_str())) == NULL)
        throw string("Fail open path \"" + path + "\"");

    while ((f_cur = readdir(dir)) != NULL) {
        struct stat sbuf;
        File file;
        string fullPath = path + "/";

        file.name = string(f_cur->d_name);
        fullPath += file.name;

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

        int fd = open(fullPath.c_str(), O_RDONLY);
        if (fd == -1)
            continue;

        /*
         * Getting size and last modify date
         */
        fstat(fd, &sbuf);
        file.modify = dateToStr(&sbuf.st_mtime);
        file.size = sbuf.st_size;
        close(fd);        

        /*
         * Generating hash of file
         */
        _fhash->open(fullPath);
        file.hash = _fhash->generate();
        _fhash->close();

        localFiles.push_back(file);
    }
    closedir(dir);
    return localFiles;
}

void FileWatch::handler()
{
    const auto &sc = _cfg->getServerCfg();
    const auto &syc = _cfg->getSyncCfg();
    vector<File> localFiles;

    try {
        localFiles = getFileList(syc.path);
    }
    catch (const string &err) {
        _log->local("FileWatch: " + err, LOG_ERROR);
        return;
    }

    try {
        _client->connect(sc.ip, sc.port);
    }
    catch (const string &err) {
        _log->local(err, LOG_ERROR);
        return;
    }

    for (const File &file : localFiles) {
        try {
            _ftransfer->openSend(syc.path + "/" + file.name, file.size);
            _ftransfer->sendFile();
            _ftransfer->close();
        }
        catch (const string &err) {
            _log->local(err, LOG_ERROR);
            continue;
        }
    }

    _client->close();
    cout << "==================================================" << endl;
}
