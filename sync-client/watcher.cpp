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


#include "watcher.h"

#include <boost/assert.hpp>


void Watcher::startWatch(unsigned delay) const
{
    timer_->start(delay);
}

void Watcher::stopWatch() const
{
    timer_->stop();
}

void Watcher::setWatcher(const shared_ptr<ITimer> &tmr)
{
    BOOST_ASSERT(tmr != nullptr);
    timer_ = tmr;
}
