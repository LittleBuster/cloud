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

#ifndef WATCHER_H
#define WATCHER_H

#include "timer.h"
#include <memory>

using namespace std;


/*
 * File watcher strategy selector
 */
class IWatcher
{
public:
    virtual ~IWatcher() {}
    virtual void startWatch(unsigned delay) const=0;
    virtual void stopWatch() const=0;
    virtual void setWatcher(const shared_ptr<ITimer> &tmr)=0;

protected:
    shared_ptr<ITimer> timer_;
};


class Watcher: public IWatcher
{
public:
    /**
     * Starting watch local folder
     * @delay: seconds
     */
    void startWatch(unsigned delay) const;

    /*
     * Stoping watch local folder
     */
    void stopWatch() const;

    /**
     * Setting watch timer
     * @tmr: variant of timer
     */
    void setWatcher(const shared_ptr<ITimer> &tmr);
};


#endif
