/*
 * Cloud: sync client application
 *
 * Copyright (C) 2016-2017 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#ifndef CLOUD_H
#define CLOUD_H

#include <string>
#include <memory>

using namespace std;

class ILog;
class IConfigs;
class ITcpClient;
class IWatcher;
class ISession;
class ITimer;


class ICloud
{
public:
    virtual void setLog(const string &filename)=0;
    virtual bool loadConfigs(const string &filename)=0;
    virtual bool login(const string &login, const string &passwd)=0;
    virtual void start()=0;
};


class Cloud: public ICloud
{
public:
    Cloud();

    /**
     * Setting path to cloud log file
     * @filename: path
     */
    void setLog(const string &filename);

    /**
     * Loading cloud configs from file
     * @filename: path to cfg file
     *
     * returns false: if fail loading
     * returns true: if loading ok
     */
    bool loadConfigs(const string &filename);

    /**
     * Open first user session and checking user
     * @login: user's name
     * @passwd: user's password
     *
     * returns flase: if bad username or password
     * returns true: if user and password ok
     */
    bool login(const string &login, const string &passwd);

    /*
     * Starting folder watcher timer
     */
    void start();

private:
    shared_ptr<ILog> log_;
    shared_ptr<IConfigs> cfg_;
    shared_ptr<ITcpClient> client_;
    shared_ptr<IWatcher> watcher_;
    shared_ptr<ISession> session_;
    shared_ptr<ITimer> masterTimer_;
    shared_ptr<ITimer> slaveTimer_;
};


#endif
