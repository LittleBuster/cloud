/* Cloud: sync client application
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#include "app.h"
#include <iostream>


App::App(const shared_ptr<ILog> &log, const shared_ptr<Configs> &cfg,
         const shared_ptr<ITimer> &fw): _log(move(log)), _cfg(move(cfg)),
         _fw(move(fw))
{
}

int App::start()
{
    cout << "Starting sync client..." << endl;
    _log->setLogFile("sync.log");

    try {
        _cfg->load("sync.cfg");
    }
    catch (const string &err) {
        _log->local("Configs: " + err, LOG_ERROR);
        return -1;
    }

    const auto &syc = _cfg->getSyncCfg();

    _fw->start(syc.interval);
    return 0;
}
