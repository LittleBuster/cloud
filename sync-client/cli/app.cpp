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
#include <thread>

#include <boost/assert.hpp>

#include "app.h"


App::App(const shared_ptr<ICloud> &cloud): cloud_(move(cloud))
{
    BOOST_ASSERT(cloud != nullptr);
}

int App::start()
{
    string login;
    string passwd;

    cloud_->setLog("cloud.log");
    if (!cloud_->loadConfigs("cloud.cfg"))
        return -1;

    cout << "Login:" << endl;
    cin >> login;
    cout << "Passwd:";
    cin >> passwd;

    if (!cloud_->login(login, passwd))
        return -1;
    cloud_->start();

    for (;;) {
        this_thread::sleep_for(1s);
    }
    return 0;
}
