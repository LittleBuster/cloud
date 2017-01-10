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

#include "cloud.h"
#include "log.h"
#include "configs.h"
#include "timer.h"
#include "mastertimer.h"
#include "tcpclient.h"
#include "session.h"
#include "watcher.h"
#include "slavetimer.h"


Cloud::Cloud()
{
    log_ = make_shared<Log>();
    cfg_ = make_shared<Configs>();
    client_ = make_shared<TcpClient>();
    watcher_ = make_shared<Watcher>();
    session_ = make_shared<Session>(client_, cfg_);
    masterTimer_ = make_shared<MasterTimer>(log_, cfg_, client_, session_);
    slaveTimer_ = make_shared<SlaveTimer>(log_, cfg_, client_, session_);
}

void Cloud::setLog(const string &filename)
{
    log_->setLogFile(filename);
}

bool Cloud::loadConfigs(const string &filename)
{
    try {
        cfg_->load(filename);
    }
    catch (const string &err) {
        log_->local("Configs: " + err, LOG_ERROR);
        return false;
    }
    return true;
}

bool Cloud::login(const string &login, const string &passwd)
{
    try {
        session_->login(login, passwd);
    } catch (const string &err) {
        log_->local("Login: " + err, LOG_ERROR);
        return false;
    }
    cout << "Login ok." << endl;
    cout << "Starting sync client..." << endl;
    cout << "Privilegies: " << session_->getPrivilegies() << endl;
    return true;
}

void Cloud::start()
{
    const auto &syc = cfg_->getSyncCfg();

    if (session_->getPrivilegies() == PV_ADMIN)
        watcher_->setWatcher(masterTimer_);
    else
        watcher_->setWatcher(slaveTimer_);
    watcher_->startWatch(syc.interval);
}
