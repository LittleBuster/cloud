// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef CLOUD_STORAGE_H_
#define CLOUD_STORAGE_H_

#include "tcpserver.h"
#include "configs.h"
#include "log.h"


enum cmd_codes {
    CMD_SEND_FILE,
    CMD_RECV_FILE,
    CMD_EXIT
};

enum answ_codes {
    ANSW_NEED_UPLOAD,
    ANSW_NOTHING
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


class ICloudStorage
{
public:
    virtual void Start(unsigned port, unsigned max_clients)=0;
};


class CloudStorage final: public ICloudStorage, public TcpServer
{
public:
    CloudStorage(const shared_ptr<IConfigs> &cfg, const shared_ptr<ILog> &log);

    void Start(unsigned port, unsigned max_clients) override final { TcpServer::Start(port, max_clients); }

private:
    const shared_ptr<IConfigs> cfg_;
    const shared_ptr<ILog> log_;

    virtual void NewSession(shared_ptr<ITcpClient> client) override final;

    virtual void AcceptError() const override final;

    virtual void ServerStarted() const override final;
};


#endif
