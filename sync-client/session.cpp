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

#include <iostream>

#include <string.h>
#include <openssl/sha.h>

#include "session.h"
#include "network.h"


Session::Session(const shared_ptr<ITcpClient> &client, const shared_ptr<IConfigs> &cfg): client_(move(client)),
                 cfg_(move(cfg))
{
    BOOST_ASSERT(client != nullptr);
    BOOST_ASSERT(cfg != nullptr);
}

void Session::login(const string &login, const string &passwd)
{
    Command cmd, answ;
    const auto& sc = cfg_->getServerCfg();

    strncpy(loginInfo_.user, login.c_str(), 19);
    genPasswdHash(loginInfo_.passwd, passwd.c_str());

    client_->connect(sc.ip, sc.port);
    cmd.code = CMD_LOGIN;
    client_->send(&cmd, sizeof(cmd));
    client_->send(&loginInfo_, sizeof(loginInfo_));
    client_->recv(&answ, sizeof(answ));
    cmd.code = CMD_EXIT;
    client_->send(&cmd, sizeof(cmd));
    client_->close();

    switch (answ.code) {
        case PV_UNKNOWN: {
            throw string("User does not exists!");
            break;
        }
        case PV_ERROR: {
            throw string("Bad user password!");
            break;
        }
        case PV_USER: {
            cout << "User authorized. Priv: USER." << endl;
            break;
        }
        case PV_ADMIN: {
            cout << "User authorized. Priv: ADMIN." << endl;
            break;
        }
    }

    priv_ = answ.code;
}

void Session::openNewSession() const
{
    Command cmd, answ;
    const auto& sc = cfg_->getServerCfg();

    client_->connect(sc.ip, sc.port);
    cmd.code = CMD_LOGIN;
    client_->send(&cmd, sizeof(cmd));
    client_->send(&loginInfo_, sizeof(loginInfo_));
    client_->recv(&answ, sizeof(answ));

    switch (answ.code) {
        case PV_UNKNOWN: {
            throw string("User does not exists!");
            break;
        }
        case PV_ERROR: {
            throw string("Bad user password!");
            break;
        }
        case PV_USER: {
            cout << "User authorized. Priv: USER." << endl;
            break;
        }
        case PV_ADMIN: {
            cout << "User authorized. Priv: ADMIN." << endl;
            break;
        }
    }
}

void Session::close() const
{
    Command cmd;

    cmd.code = CMD_EXIT;
    client_->send(&cmd, sizeof(cmd));
    client_->close();
}

const LoginInfo& Session::getLoginInfo() const
{
    return loginInfo_;
}

unsigned Session::getPrivilegies() const
{
    return priv_;
}

void Session::genPasswdHash(char *outHash, const char *passwd)
{
    SHA512_CTX sha;
    unsigned char hash[SHA512_DIGEST_LENGTH];

    SHA512_Init(&sha);
    SHA512_Update(&sha, passwd, strlen(passwd));
    SHA512_Final(hash, &sha);

    memset(outHash, 0x00, 515);
    strcpy(outHash, "");

    for (unsigned i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        char sym[4];

        sprintf(sym, "%02X", hash[i]);
        strcat(outHash, sym);
    }
}
