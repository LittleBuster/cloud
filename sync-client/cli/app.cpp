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

#include "app.h"
#include "../session.h"


App::App(const shared_ptr<ILog> &log, const shared_ptr<Configs> &cfg,
         const shared_ptr<ITimer> &file_watch, const shared_ptr<ISession> &session): log_(move(log)),
         cfg_(move(cfg)), file_watch_(move(file_watch)), session_(move(session))
{
}

int App::start()
{
    cout << "Starting sync client..." << endl;
    log_->SetLogFile("sync.log");

    try {
        cfg_->Load("sync.cfg");
    }
    catch (const string &err) {
        log_->Local("Configs: " + err, LOG_ERROR);
        return -1;
    }

    const auto &syc = cfg_->GetSyncCfg();

    try {
        session_->Login("serg", "123");
    } catch (const string &err) {
        log_->Local("Login: " + err, LOG_ERROR);
        return -1;
    }
    cout << "Login ok." << endl;

    file_watch_->Start(syc.interval);
    return 0;
}
