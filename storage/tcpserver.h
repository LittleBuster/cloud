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


#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <memory>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "tcpclient.h"

#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR (-1)
#define SOCKET int

using namespace std;


class ITcpServer
{
public:
    virtual void newSession(shared_ptr<ITcpClient> client)=0;
    virtual void acceptError() const=0;
    virtual void serverStarted() const=0;
    virtual void start(unsigned port, unsigned max_clients)=0;
};


class TcpServer: public ITcpServer
{
public:

    /*
     * New client connection session
     */
    virtual void newSession(shared_ptr<ITcpClient> client) { }

    /*
     * Accepting new client error signal
     */
    virtual void acceptError() const { }

    /*
     * Server started signal
     */
    virtual void serverStarted() const { }

    /**
     * Binding tcp server
     * @port: local tcp port
     *
     * throw: error if fail binding
     */
    void start(unsigned port, unsigned max_clients);

private:
    SOCKET sock_;
};


#endif
