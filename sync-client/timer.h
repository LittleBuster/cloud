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

#ifndef __TIMER_H__
#define __TIMER_H__

#include <functional>


using namespace std;


class ITimer
{
public:
    virtual void handler()=0;
    virtual void start(unsigned delay)=0;
    virtual void stop()=0;
};


class Timer: public ITimer
{
private:
    bool _isOn = false;
    unsigned _delay;

    void loop();

public:
    virtual void handler() { }

    /**
     * Starting timer with delay
     * @delay: milleseconds
     */
    void start(unsigned delay);

    /*
     *  Stopping timer
     */
    void stop();
};


#endif
