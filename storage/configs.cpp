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

#include "configs.h"
#include "ext.h"


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
    char line[255];

    while (1) {
        file_.getline(line, 255);
        if (line[0] != '#' && line[0] != '/' && line[0] != '\n' && string(line) != "")
            break;
    }
    const auto out = ext::split_string(line, '=');
    return get<1>(out);
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
        sc_.port = static_cast<unsigned>(atoi(cfg.readString().c_str()));
        sc_.max_users = static_cast<unsigned>(atoi(cfg.readString().c_str()));
        syc_.path = cfg.readString();
        ubc_.path = cfg.readString();
        fbc_.path = cfg.readString();
    }
    catch (...) {
        throw string("Fail reading configs values.");
    }
}
