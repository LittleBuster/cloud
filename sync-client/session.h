// Cloud: sync client application
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

#include <string>
#include <memory>

#include "network.h"
#include "tcpclient.h"
#include "configs.h"

using namespace std;

typedef enum {
    PV_ADMIN,
    PV_USER,
    PV_UNKNOWN
} Privilegies;

typedef struct {
    char user[20];
    char passwd[515];
} LoginInfo;


class ISession
{
public:
    virtual void Login(const string &login, const string &passwd)=0;
    virtual void OpenNewSession()=0;
    virtual void CloseSession()=0;
    virtual const LoginInfo& GetLoginInfo() const=0;
    virtual unsigned GetPrivilegies() const=0;
};


class Session: public ISession
{
public:
    Session(const shared_ptr<ITcpClient> &client, const shared_ptr<IConfigs> &cfg);

    void Login(const string &login, const string &passwd);

    void OpenNewSession();

    void CloseSession();

    const LoginInfo& GetLoginInfo() const;

    unsigned GetPrivilegies() const;

private:
    const shared_ptr<ITcpClient> client_;
    const shared_ptr<IConfigs> cfg_;
    LoginInfo login_info_;
    unsigned priv_;

    void GeneratePasswordHash(char *out_hash, const char *passwd);
};


#endif
