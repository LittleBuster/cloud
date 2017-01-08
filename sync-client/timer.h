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


#ifndef TIMER_H
#define TIMER_H


typedef struct {
    unsigned long size;
    char hash[515];
    char filename[255];
    char modify_time[50];
} FileInfo;


class ITimer
{
public:
    virtual void handler() {}
    virtual void start(unsigned delay)=0;
    virtual void stop() const=0;
};


#endif
