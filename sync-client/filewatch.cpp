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
#include <vector>
#include <ctime>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>


FileWatch::FileWatch(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg):
                     _log(move(log)), _cfg(move(cfg))
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
    int fd;
    DIR *dir;
    struct dirent *f_cur;
    vector<File> flist;

    if ((dir = opendir(path.c_str())) == NULL)
        throw string("Can not open directory.");

    while ((f_cur = readdir(dir)) != NULL) {
        File file;
        struct stat sbuf;
        string fullPath = path + "/";

        file.name = string(f_cur->d_name);
        fullPath += file.name;
        /*
         * Ignoring hidden files and up folders
         */
        if (file.name == "." || file.name == "..")
            continue;

        fd = open(fullPath.c_str(), O_RDONLY);
        if (fd == -1)
            continue;

        fstat(fd, &sbuf);
        file.size = sbuf.st_size;
        file.modify = dateToStr(&sbuf.st_mtime);
        ::close(fd);
        flist.push_back(file);
    }
    closedir(dir);
    return flist;
}

void FileWatch::handler()
{
    const auto &syc = _cfg->getSyncCfg();
    vector<File> localFiles = getFileList(syc.path);

    for (const File &file : localFiles) {
        cout << file.name << " " << file.size << " " << file.modify << endl;
    }
    cout << "==========" << endl;
}
