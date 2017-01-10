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


#ifndef SESSION_H
#define SESSION_H

#include <mutex>

#include "configs.h"
#include "tcpclient.h"
#include "usersbase.h"
#include "filesbase.h"


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
    virtual void openNewSession()=0;
    virtual void close()=0;
    virtual unsigned getPrivilegies()=0;
};


class Session: public ISession
{
public:
    Session(const shared_ptr<ITcpClient> &client, const shared_ptr<IConfigs> &cfg,
            const shared_ptr<IUsersBase> &ub, mutex &mtx);

    void openNewSession();

    void close();

    unsigned getPrivilegies();

private:
    const shared_ptr<ITcpClient> client_;
    const shared_ptr<IConfigs> cfg_;
    const shared_ptr<IUsersBase> ub_;
    unsigned priv_;
    mutex &mtx_;

    inline void setCurrentPriv(unsigned priv);
};


#endif
