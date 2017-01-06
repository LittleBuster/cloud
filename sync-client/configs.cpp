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


#include <string.h>
#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "configs.h"


ConfigsFile::ConfigsFile(const string &filename)
{
    file_.open(filename);
}

ConfigsFile::~ConfigsFile()
{
    if (file_.is_open())
        file_.close();
}

string ConfigsFile::readString()
{
    string line;
    vector<string> out;

    while (1) {
        file_ >> line;
        if (line[0] != '#' && line[0] != '/' && line[0] != '\n' && string(line) != "")
            break;
    }
    boost::split(out, line, boost::is_any_of("="));
    return out[1];
}

bool ConfigsFile::isOpen() const
{
    return file_.is_open();
}


void Configs::load(const string &filename)
{
    ConfigsFile cfg(filename);

    if (!cfg.isOpen())
        throw string("File not found.");

    try {
        sc_.ip = cfg.readString();
        sc_.port = boost::lexical_cast<unsigned>(cfg.readString());
        syc_.path = cfg.readString();
        syc_.interval = boost::lexical_cast<unsigned>(cfg.readString());
    } catch (...) {
        throw string("Fail parsing configs.");
    }
}
