/*
 * Cloud: sync client application
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
#include "../log.h"
#include "../configs.h"
#include "../timer.h"
#include "../mastertimer.h"
#include "../tcpclient.h"
#include "../session.h"
#include "../watcher.h"
#include "../slavetimer.h"


int main()
{
    auto log = make_shared<Log>();
    auto cfg = make_shared<Configs>();
    auto client = make_shared<TcpClient>();
    auto watcher = make_shared<Watcher>();
    auto session = make_shared<Session>(client, cfg);
    auto masterTimer = make_shared<MasterTimer>(log, cfg, client, session);
    auto slaveTimer = make_shared<SlaveTimer>(log, cfg, client, session);
    auto app = make_shared<App>(log, cfg, masterTimer, session, watcher, slaveTimer);

    return app->start();
}
