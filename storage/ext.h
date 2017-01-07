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


#ifndef EXT_H
#define EXT_H

#include <string>
#include <vector>
#include <tuple>
#include <ctime>

using namespace std;


namespace ext {


tuple<string, string> split_string(const string &str, char sym);

const string current_datetime();

const string ftoa(float num);

int pos(const string &str, const char sym);

string date_to_str(time_t *time);


}


#endif
