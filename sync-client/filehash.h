// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef FILEHASH_H_
#define FILEHASH_H_

#include <string>
#include <fstream>

using namespace std;


class FileHash
{
public:
    FileHash(const string &filename);

    ~FileHash();

    string Generate();

private:
    ifstream file_;

    string HashToStr(const unsigned char *hash);
};


#endif
