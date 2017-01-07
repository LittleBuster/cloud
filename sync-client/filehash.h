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


#ifndef FILE_HASH_H
#define FILE_HASH_H

#include <string>
#include <fstream>

using namespace std;


class FileHash
{
public:
    FileHash(const string &filename);
    ~FileHash();
    string generate();

private:
    ifstream file_;

    string hashToStr(const unsigned char *hash);
};


#endif
