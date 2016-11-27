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

#ifndef __APP_H__
#define __APP_H__

#include "log.h"
#include "configs.h"
#include "filewatch.h"


class App
{
private:
    const shared_ptr<ILog> _log;
    const shared_ptr<IConfigs> _cfg;
    const shared_ptr<ITimer> _fw;

public:
    App(const shared_ptr<ILog> &log, const shared_ptr<Configs> &cfg,
        const shared_ptr<ITimer> &fw);

    int start();
};


#endif
