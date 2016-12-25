// Cloud: storage application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef BASE_H_
#define BASE_H_

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
    virtual void Open(const string &filename)=0;
    virtual bool Exists(const User &user)=0;
    virtual bool Verify(const User &user)=0;
    virtual unsigned GetUserPriv(const User &user)=0;
    virtual void Close()=0;
};


class UsersBase: public IUsersBase
{
public:
    void Open(const string &filename);

    bool Exists(const User &user);

    unsigned GetUserPriv(const User &user);

    bool Verify(const User &user);

    void Close();

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
    virtual void Open(const string &filename)=0;
    virtual void AddFile(const File &file)=0;
    virtual bool Exists(const File &file)=0;
    virtual bool Verify(const File &file)=0;
    virtual void Close()=0;
};


class FilesBase: public IFilesBase
{
public:
    void Open(const string &filename);

    void AddFile(const File &file);

    bool Exists(const File &file);

    bool Verify(const File &file);

    void Close();

private:
    sqlite3 *base_;
};

#endif
