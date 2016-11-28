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

#ifndef __FILEHASH_H__
#define __FILEHASH_H__

#include <string>
#include <fstream>

using namespace std;


class IFileHash
{
public:
    virtual void open(const string &filename)=0;
    virtual string generate()=0;
    virtual void close()=0;
};


class FileHash: public IFileHash
{
private:
    ifstream _file;

    string hashToStr(const unsigned char *hash);

public:
    void open(const string &filename);

    string generate();

    void close();
};


#endif
