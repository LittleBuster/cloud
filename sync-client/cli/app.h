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


#ifndef APP_H_
#define APP_H_

#include "../cloud.h"


class App
{
public:
    App(const shared_ptr<ICloud> &cloud);

    int start();

private:
    const shared_ptr<ICloud> cloud_;
};


#endif
