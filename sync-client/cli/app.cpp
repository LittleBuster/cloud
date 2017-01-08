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

#include <boost/thread.hpp>

#include "app.h"
#include "../session.h"


App::App(const shared_ptr<ILog> &log, const shared_ptr<Configs> &cfg,
         const shared_ptr<ITimer> &masterTimer, const shared_ptr<ISession> &session,
         const shared_ptr<IWatcher> &watcher, const shared_ptr<ITimer> &slaveTimer): log_(move(log)),
         cfg_(move(cfg)), masterTimer_(move(masterTimer)), session_(move(session)),
         watcher_(move(watcher)), slaveTimer_(move(slaveTimer))
{
}

int App::start()
{
    string login;
    string passwd;

    log_->setLogFile("sync.log");

    try {
        cfg_->load("sync.cfg");
    }
    catch (const string &err) {
        log_->local("Configs: " + err, LOG_ERROR);
        return -1;
    }

    const auto &syc = cfg_->getSyncCfg();

    cout << "Login: ";
    cin >> login;
    cout << "Passwd: ";
    cin >> passwd;

    try {
        session_->login(login, passwd);
    } catch (const string &err) {
        log_->local("Login: " + err, LOG_ERROR);
        return -1;
    }
    cout << "Login ok." << endl;
    cout << "Starting sync client..." << endl;
    cout << "Privilegies: " << session_->getPrivilegies() <<endl;

    if (session_->getPrivilegies() == PV_ADMIN)
        watcher_->setWatcher(masterTimer_);
    else
        watcher_->setWatcher(slaveTimer_);
    watcher_->startWatch(syc.interval);

    for (;;) {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }
    return 0;
}
