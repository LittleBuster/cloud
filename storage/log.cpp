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


#include <iostream>
#include <fstream>

#include "log.h"
#include "ext.h"


Log::Log(): logPath_("")
{
}

string Log::makeLogMsg(const string &msg, const LogType type) const
{
    string out;

    const auto &dt = ext::split_string(ext::current_datetime(), ' ');
    out = "[" + get<0>(dt) + "][" + get<1>(dt) + "][";

    switch (type) {
        case LOG_ERROR: {
            out += "ERROR] ";
            break;
        }
        case LOG_WARNING: {
            out += "WARNING] ";
            break;
        }
        case LOG_INFORMATION: {
            out += "INFO] ";
            break;
        }
    }
    out += msg;
    return out;
}

void Log::local(const string &message, const LogType log_type)
{
    const string& msg = makeLogMsg(message, log_type);
    cout << msg << endl;

    if (logPath_ == "")
        return;

    try {
        ofstream log;
        log.open(logPath_, ios::out|ios::ate|ios::app);
        log << msg << "\n";
        log.close();
    }
    catch (...) {
        cout << "Fail writing to log file." << endl;
    }
}
