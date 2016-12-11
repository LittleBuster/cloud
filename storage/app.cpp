// Cloud: storage application
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


App::App(const shared_ptr<ILog> &log, const shared_ptr<Configs> &cfg,
         const shared_ptr<ICloudStorage> &storage): log_(move(log)), cfg_(move(cfg)),
         storage_(move(storage))
{
}

int App::start()
{
    cout << "Starting Cloud Storage server..." << endl;
    log_->SetLogFile("storage.log");

    try {
        cfg_->Load("storage.cfg");
    }
    catch (const string &err) {
        log_->Local("Configs: " + err, LOG_ERROR);
        return -1;
    }

    const auto &sc = cfg_->GetServerCfg();

    storage_->Start(sc.port, sc.max_users);
    return 0;
}
