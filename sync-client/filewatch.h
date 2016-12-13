// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef FILE_WATCH_H_
#define FILE_WATCH_H_

#include <vector>

#include "timer.h"
#include "log.h"
#include "configs.h"
#include "filehash.h"
#include "tcpclient.h"
#include "filetransfer.h"
#include "session.h"


typedef struct {
    unsigned long size;
    string name;
    string hash;
    string modify;    
} File;

typedef struct {
    unsigned long size;
    char hash[515];
    char filename[255];
    char modify_time[50];
} FileInfo;


class MasterWatch: public Timer
{
public:
    MasterWatch(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg,
              const shared_ptr<ITcpClient> &client, const shared_ptr<ISession> &session);

    virtual void Handler() override final;

private:
    const shared_ptr<ILog> log_;
    const shared_ptr<IConfigs> cfg_;
    const shared_ptr<ITcpClient> client_;
    const shared_ptr<ISession> session_;

    vector<File> GetFileList(const string &path);
};


#endif
