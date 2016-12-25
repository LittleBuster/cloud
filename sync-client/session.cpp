// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include <iostream>

#include <string.h>
#include <openssl/sha.h>

#include "session.h"
#include "network.h"


Session::Session(const shared_ptr<ITcpClient> &client, const shared_ptr<IConfigs> &cfg): client_(move(client)),
                 cfg_(move(cfg))
{
}

void Session::Login(const string &login, const string &passwd)
{
    Command cmd, answ;
    const auto& sc = cfg_->GetServerCfg();

    strncpy(login_info_.user, login.c_str(), 19);
    GeneratePasswordHash(login_info_.passwd, passwd.c_str());

    client_->Connect(sc.ip, sc.port);
    cmd.code = CMD_LOGIN;
    client_->Send(&cmd, sizeof(cmd));
    client_->Send(&login_info_, sizeof(login_info_));
    client_->Recv(&answ, sizeof(answ));
    cmd.code = CMD_EXIT;
    client_->Send(&cmd, sizeof(cmd));
    client_->Close();

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

void Session::OpenNewSession()
{
    Command cmd, answ;
    const auto& sc = cfg_->GetServerCfg();

    client_->Connect(sc.ip, sc.port);
    cmd.code = CMD_LOGIN;
    client_->Send(&cmd, sizeof(cmd));
    client_->Send(&login_info_, sizeof(login_info_));
    client_->Recv(&answ, sizeof(answ));

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

void Session::CloseSession()
{
    Command cmd;

    cmd.code = CMD_EXIT;
    client_->Send(&cmd, sizeof(cmd));
    client_->Close();
}

const LoginInfo& Session::GetLoginInfo() const
{
    return login_info_;
}

unsigned Session::GetPrivilegies() const
{
    return priv_;
}

void Session::GeneratePasswordHash(char *out_hash, const char *passwd)
{
    SHA512_CTX sha;
    unsigned char hash[SHA512_DIGEST_LENGTH];

    SHA512_Init(&sha);
    SHA512_Update(&sha, passwd, strlen(passwd));
    SHA512_Final(hash, &sha);

    memset(out_hash, 0x00, 515);
    strcpy(out_hash, "");

    for (unsigned i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        char sym[4];

        sprintf(sym, "%02X", hash[i]);
        strcat(out_hash, sym);
    }
}
