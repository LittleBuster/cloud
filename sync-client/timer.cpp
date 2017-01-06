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


#include "timer.h"


void Timer::handler()
{
    timer_->expires_at(timer_->expires_at() + boost::posix_time::seconds(delay_));
    timer_->async_wait(bind(&Timer::handler, this));
}

void Timer::start(unsigned delay)
{
    delay_ = delay;
    timer_ = make_shared<deadline_timer>(io_, boost::posix_time::seconds(delay_));
    timer_->async_wait(bind(&Timer::handler, this));
    io_.run();
}

void Timer::stop()
{
    timer_.reset();
}
