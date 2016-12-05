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


class IFileHash
{
public:
    virtual void Open(const string &filename)=0;
    virtual string Generate()=0;
    virtual void Close()=0;
};


class FileHash: public IFileHash
{
public:
    void Open(const string &filename);

    string Generate();

    void Close();

private:
    ifstream file_;

    string HashToStr(const unsigned char *hash);
};


#endif
