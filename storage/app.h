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

#ifndef APP_H
#define APP_H

#include "log.h"
#include "configs.h"
#include "cloudstorage.h"


class App
{
public:
    App(const shared_ptr<ILog> &log, const shared_ptr<Configs> &cfg, const shared_ptr<ICloudStorage> &storage);

    int start();

private:
    const shared_ptr<ILog> log_;
    const shared_ptr<IConfigs> cfg_;
    const shared_ptr<ICloudStorage> storage_;
};


#endif
