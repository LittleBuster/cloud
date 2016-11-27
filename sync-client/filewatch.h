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

#ifndef __FILEWATCH_H__
#define __FILEWATCH_H__

#include <vector>
#include "timer.h"
#include "log.h"
#include "configs.h"

typedef struct {
    string name;
    unsigned long size;
    string modify;
} File;


class FileWatch: public Timer
{
private:
    const shared_ptr<ILog> _log;
    const shared_ptr<IConfigs> _cfg;

    string dateToStr(time_t *time);

    vector<File> getFileList(const string &path);

public:
    FileWatch(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg);

    virtual void handler() override final;
};


#endif
