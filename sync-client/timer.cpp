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

#include "timer.h"


void Timer::start()
{
    _isRun = true;
    _timer = make_shared<boost::asio::deadline_timer>(_io, boost::posix_time::seconds(_interval));

    while (_isRun) {
        _timer->wait();
        handler();
        _timer->expires_at(_timer->expires_at() + boost::posix_time::seconds(_interval));
    }
}

void Timer::stop()
{
    _isRun = false;
    _io.stop();
}
