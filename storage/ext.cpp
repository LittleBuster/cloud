// Cloud: storage application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <sstream>

#include "ext.h"


namespace ext {


tuple<string, string> split_string(const string &str, char sym)
{
    bool is_found = false;
    string left = "";
    string right = "";

    for (const auto &s : str) {
        if (s == sym) {
            is_found = true;
            continue;
        }

        if (!is_found)
            left += s;

        if (is_found)
            right += s;
    }

    if (!is_found)
        throw string("Split symbol not found.");

    if (left == "" || right == "")
        throw string("Incorrect string for splitting.");

    return make_tuple(left, right);
}

const string current_datetime()
{
    time_t now = time(0);
    struct tm time_struct;
    char buf[80];

    time_struct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &time_struct);

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

string date_to_str(time_t *time)
{
    char time_str[20];
    char date_str[20];
    struct tm *time_info;
    string out;

    time_info = localtime(time);
    strftime(date_str, 20, "%F", time_info);
    strftime(time_str, 20, "%T", time_info);

    out = string(date_str) + " " + string(time_str);
    return out;
}


}
