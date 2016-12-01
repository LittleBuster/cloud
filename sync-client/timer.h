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

#include <memory>
#include <boost/asio.hpp>


using namespace std;


class ITimer
{
public:
    virtual void handler()=0;
    virtual void setInterval(unsigned interval)=0;
    virtual void start()=0;
    virtual void stop()=0;
};


class Timer: public ITimer
{
private:
    bool _isRun = false;
    unsigned _interval;
    boost::asio::io_service _io;
    shared_ptr<boost::asio::deadline_timer> _timer;

public:
    virtual void handler() { start(); }

    inline void setInterval(unsigned interval) { _interval = interval; }

    void start();

    void stop();
};


#endif
