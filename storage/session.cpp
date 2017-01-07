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


#include <iostream>

#include "session.h"
#include "network.h"


Session::Session(const shared_ptr<ITcpClient> &client, const shared_ptr<IConfigs> &cfg, const shared_ptr<IUsersBase> &ub, mutex &mtx):
    client_(move(client)), cfg_(move(cfg)), ub_(move(ub)), mtx_(mtx)
{    
}

void Session::openNewSession()
{
    User user;
    Command answ;
    LoginInfo info;
    const auto &ubc = cfg_->getUsersBaseCfg();

    client_->recv(&info, sizeof(info));

    user.name = string(info.user);
    user.passwd = string(info.passwd);

    cout << "New client connected: " << user.name << endl;

    mtx_.lock();
    ub_->open(ubc.path);
    if (!ub_->exists(user)) {
        answ.code = PV_UNKNOWN;
        client_->send(&answ, sizeof(answ));
        mtx_.unlock();
        throw string("Unknown user.");
    }
    else if (!ub_->verify(user)) {
        answ.code = PV_ERROR;
        client_->send(&answ, sizeof(answ));
        mtx_.unlock();
        throw string("Bad user password.");
    }
    cout << "Authorization ok." << endl;

    answ.code = ub_->getUserPriv(user);
    setCurrentPriv(answ.code);
    ub_->close();
    mtx_.unlock();

    client_->send(&answ, sizeof(answ));
}

void Session::close()
{
    client_->close();
}

unsigned Session::getPrivilegies()
{
    return priv_;
}

void Session::setCurrentPriv(unsigned priv)
{
    priv_ = priv;
}
