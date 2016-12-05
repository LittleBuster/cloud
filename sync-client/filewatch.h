// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef FILEWATCH_H_
#define FILEWATCH_H_


#include <vector>

#include "timer.h"
#include "log.h"
#include "configs.h"
#include "filehash.h"
#include "tcpclient.h"
#include "filetransfer.h"


typedef struct {
    string name;
    string hash;
    string modify;
    unsigned long size;
} File;

enum cmds_codes {
    CMD_SEND_FILE,
    CMD_RECV_FILE,
    CMD_EXIT
};

typedef struct {
    unsigned code;
} Command;

typedef struct {
    unsigned long size;
    char modify_time[50];
    char filename[255];
    char hash[515];
} FileInfo;


class FileWatch: public Timer
{
private:
    const shared_ptr<ILog> log_;
    const shared_ptr<IConfigs> cfg_;
    const shared_ptr<ITcpClient> client_;

    vector<File> GetFileList(const string &path);

public:
    FileWatch(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg,
              const shared_ptr<ITcpClient> &client);

    virtual void Handler() override final;
};


#endif
