/*
 * Cloud: sync client application
 *
 * Copyright (C) 2016-2017 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */


#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <memory>

#include "network.h"
#include "tcpclient.h"
#include "configs.h"

using namespace std;

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
    virtual void login(const string &login, const string &passwd)=0;
    virtual void openNewSession() const=0;
    virtual void close() const=0;
    virtual const LoginInfo& getLoginInfo() const=0;
    virtual unsigned getPrivilegies() const=0;
};


class Session: public ISession
{
public:
    Session(const shared_ptr<ITcpClient> &client, const shared_ptr<IConfigs> &cfg);

    /**
     * First sending login info
     * @login: name of user
     * @passwd: user password
     *
     * throw: error if login fail
     */
    void login(const string &login, const string &passwd);

    /**
     * Regular sending exists login info
     *
     * throw: error if login fail
     */
    void openNewSession() const;

    /*
     * Sending close session information
     */
    void close() const;

    const LoginInfo& getLoginInfo() const;
    unsigned getPrivilegies() const;

private:
    const shared_ptr<ITcpClient> client_;
    const shared_ptr<IConfigs> cfg_;
    LoginInfo loginInfo_;
    unsigned priv_;

    void genPasswdHash(char *outHash, const char *passwd);
};


#endif
