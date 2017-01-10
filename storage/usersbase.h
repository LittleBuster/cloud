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


#ifndef USERSBASE_H
#define USERSBASE_H

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
    /**
     * Load database with users
     * @filename: path to database
     */
    void open(const string &filename);

    /*
     * Existing user
     */
    bool exists(const User &user);

    /*
     * User's privilegies
     */
    unsigned getUserPriv(const User &user);

    /*
     * Checking user password
     */
    bool verify(const User &user);

    /*
     * Closing database
     */
    void close();

private:
    sqlite3 *base_;
};


#endif
