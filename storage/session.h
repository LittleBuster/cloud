// Cloud: storage application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef SESSION_H_
#define SESSION_H_

#include <mutex>

#include "configs.h"
#include "tcpclient.h"
#include "base.h"


typedef enum {
    PV_ADMIN = 100,
    PV_USER = 101,
    PV_UNKNOWN = 102,
    PV_ERROR = 103
} Privilegies;

typedef struct {
    char user[20];
    char passwd[515];
} LoginInfo;


class ISession
{
public:
    virtual void OpenNewSession()=0;
    virtual void Close()=0;
    virtual unsigned GetPrivilegies()=0;
};


class Session: public ISession
{
public:
    Session(const shared_ptr<ITcpClient> &client, const shared_ptr<IConfigs> &cfg,
            const shared_ptr<IUsersBase> &ub, mutex &mtx);

    void OpenNewSession();

    void Close();

    unsigned GetPrivilegies();

private:
    const shared_ptr<ITcpClient> client_;
    const shared_ptr<IConfigs> cfg_;
    const shared_ptr<IUsersBase> ub_;
    unsigned priv_;
    mutex &mtx_;

    inline void SetCurrentPriv(unsigned priv);
};


#endif
