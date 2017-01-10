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


#ifndef CLOUD_STORAGE_H
#define CLOUD_STORAGE_H

#include <mutex>

#include "tcpserver.h"
#include "configs.h"
#include "log.h"
#include "base.h"


typedef struct {
    unsigned long size;
    char hash[515];
    char filename[255];
    char modify_time[50];
} FileInfo;


class ICloudStorage
{
public:
    virtual void start(unsigned port, unsigned max_clients)=0;
};


class CloudStorage final: public ICloudStorage, public TcpServer
{
public:
    CloudStorage(const shared_ptr<IConfigs> &cfg, const shared_ptr<ILog> &log, const shared_ptr<IUsersBase> &usersBase,
                 const shared_ptr<IFilesBase> &filesBase);

    void start(unsigned port, unsigned max_clients) override final { TcpServer::start(port, max_clients); }

private:
    const shared_ptr<IConfigs> cfg_;
    const shared_ptr<ILog> log_;
    const shared_ptr<IUsersBase> usersBase_;
    const shared_ptr<IFilesBase> filesBase_;
    mutex mtx_;

    virtual void newSession(shared_ptr<ITcpClient> client) override final;

    virtual void acceptError() const override final;

    virtual void serverStarted() const override final;

    void cleanFiles(const vector<string> &files);
};


#endif
