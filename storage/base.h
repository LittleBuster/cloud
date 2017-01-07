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


#ifndef BASE_H
#define BASE_H

#include <vector>
#include <string>

#include <sqlite3.h>

using namespace std;


typedef struct {
    string name;
    string passwd;
} User;


class IUsersBase
{
public:
    virtual void open(const string &filename)=0;
    virtual bool exists(const User &user)=0;
    virtual bool verify(const User &user)=0;
    virtual unsigned getUserPriv(const User &user)=0;
    virtual void close()=0;
};


class UsersBase: public IUsersBase
{
public:
    void open(const string &filename);

    bool exists(const User &user);

    unsigned getUserPriv(const User &user);

    bool verify(const User &user);

    void close();

private:
    sqlite3 *base_;
};


typedef struct {
    unsigned long size;
    string hash;
    string filename;
    string modify;
} File;


class IFilesBase
{
public:
    virtual void open(const string &filename)=0;
    virtual void addFile(const File &file)=0;
    virtual bool exists(const File &file)=0;
    virtual bool verify(const File &file)=0;
    virtual void close()=0;
};


class FilesBase: public IFilesBase
{
public:
    void open(const string &filename);

    void addFile(const File &file);

    bool exists(const File &file);

    bool verify(const File &file);

    void close();

private:
    sqlite3 *base_;
};

#endif
