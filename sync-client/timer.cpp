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


void Timer::loop()
{
    while (_isOn) {
        handler();

        int CLOCKS_PER_MSEC = CLOCKS_PER_SEC / 1000;
        clock_t end_time = clock() + _delay * CLOCKS_PER_MSEC;
        while (clock() < end_time) {}
    }
}

void Timer::start(unsigned delay)
{
    _delay = delay;
    _isOn = true;
    loop();
}

void Timer::stop()
{
    _isOn = false;
}
