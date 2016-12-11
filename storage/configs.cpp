// Cloud: storage application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <string.h>
#include <fstream>
#include <iostream>

#include "configs.h"
#include "ext.h"


string Configs::ReadString(ifstream &is) const
{
    char line[255];

    while (1) {
        memset(line, 0x00, 255);
        is.getline(line, 255);
        if (line[0] != '#' && line[0] != '/' && line[0] != '\n' && string(line) != "")
            break;
    }
    const auto &param = ext::split_string(string(line), '=');
    return get<1>(param);
}

int Configs::ReadInt(ifstream &is) const
{
    char line[255];

    while (1) {
        is.getline(line, 255);
        if (line[0] != '#' && line[0] != '/' && line[0] != '\n' && string(line) != "")
            break;
    }

    const auto &param = ext::split_string(string(line), '=');
    return atoi(get<1>(param).c_str());
}


void Configs::Load(const string &filename)
{
    ifstream ifs;

    ifs.open(filename);
    if (!ifs.is_open())
        throw string("File not found.");

    try {
        sc_.port = static_cast<unsigned>(ReadInt(ifs));
        sc_.max_users = static_cast<unsigned>(ReadInt(ifs));
        syc_.path = ReadString(ifs);
    }
    catch (...) {
        ifs.close();
        throw string("Fail reading configs values.");
    }
    ifs.close();
}
