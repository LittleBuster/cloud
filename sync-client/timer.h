// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef TIMER_H_
#define TIMER_H_

#include <functional>


using namespace std;


class ITimer
{
public:
    virtual void Handler()=0;
    virtual void Start(unsigned delay)=0;
    virtual void Stop()=0;
};


class Timer: public ITimer
{
public:
    virtual void Handler() { }

    /**
     * Starting timer with delay
     * @delay: milleseconds
     */
    void Start(unsigned delay);

    /*
     *  Stopping timer
     */
    void Stop();

private:
    bool is_on_ = false;
    unsigned delay_;

    void Loop();
};


#endif
