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


class UsersBase
{
public:
    void Open(const string &filename);

    bool Exists(const User &user);

    bool Verify(const User &user);

    void Close();

private:
    sqlite3 *base_;
};


#endif
