// Cloud: storage application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <iostream>

#include "base.h"


typedef struct {
    string passwd;
    bool result;
} VerifyData;


static int ExistsCb(void *data, int argc, char **argv, char **col_name)
{
    bool *exists = reinterpret_cast<bool*>(data);

    if (argc != 0)
        *exists = true;
    else
        *exists = false;
    return 0;
}

static int VerifyCb(void *data, int argc, char **argv, char **col_name)
{
    VerifyData *verify = reinterpret_cast<VerifyData*>(data);

    if (string(argv[2]) != verify->passwd)
        verify->result = false;
    else
        verify->result = true;
    return 0;
}


void UsersBase::Open(const string &filename)
{
    int ret_val;

    ret_val = sqlite3_open(filename.c_str(), &base_);
    if(ret_val)
        throw string("Can not connect to database.");
}

bool UsersBase::Exists(const User &user)
{
    int ret_val;
    bool exists;
    char *err_msg = 0;

    string sql = "SELECT * FROM users WHERE name=\"" + user.name + "\"";

    ret_val = sqlite3_exec(base_, sql.c_str(), ExistsCb, reinterpret_cast<void*>(&exists), &err_msg);
    if (ret_val != SQLITE_OK) {
        string err(err_msg);
        sqlite3_free(err_msg);
        throw string("UsersBase exists: " + err);
    }
    return exists;
}

bool UsersBase::Verify(const User &user)
{
    int ret_val;
    char *err_msg = 0;
    VerifyData data;

    data.passwd = user.passwd;
    string sql = "SELECT * FROM users WHERE name=\"" + user.name + "\"";

    ret_val = sqlite3_exec(base_, sql.c_str(), VerifyCb, reinterpret_cast<void*>(&data), &err_msg);
    if (ret_val != SQLITE_OK) {
        string err(err_msg);
        sqlite3_free(err_msg);
        throw string("UsersBase verify: " + err);
    }
    return data.result;
}

void UsersBase::Close()
{
    sqlite3_close(base_);
}
