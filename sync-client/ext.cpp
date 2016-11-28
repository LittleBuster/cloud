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


#include "ext.h"
#include <sstream>


namespace ext {


tuple<string, string> split_string(const string &str, char sym)
{
    bool isFind = false;
    string out1 = "";
    string out2 = "";

    for (const auto &s : str) {
        if (s == sym) {
            isFind = true;
            continue;
        }

        if (!isFind)
            out1 += s;

        if (isFind)
            out2 += s;
    }

    if (!isFind)
        throw string("Split symbol not found.");

    if (out1 == "" || out2 == "")
        throw string("Incorrect string for splitting.");

    return make_tuple(out1, out2);
}

const string current_datetime()
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];

    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}

const string ftoa(float num)
{
    ostringstream buff;
    buff << num;
    return buff.str();
}

int pos(const string &str, const char sym)
{
    int i = 0;

    for (const auto &c : str) {
        if (c == sym)
            return i;
        i++;
    }
    return -1;
}


}
