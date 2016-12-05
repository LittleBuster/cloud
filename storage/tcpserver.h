// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include <memory>
#include <thread>

#ifdef WIN32
    #include <Windows.h>
    #include <Winsock2.h>
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <string.h>

    #define INVALID_SOCKET (SOCKET)(~0)
    #define SOCKET_ERROR (-1)
    #define SOCKET int
#endif

#include "tcpclient.h"

using namespace std;


class ITcpServer
{
public:
    virtual void NewSession(shared_ptr<ITcpClient> client)=0;
    virtual void AcceptError() const=0;
    virtual void ServerStarted() const=0;
    virtual void Start(unsigned port, unsigned max_clients)=0;
};


class TcpServer: public ITcpServer
{
public:
    // New client connection session
    virtual void NewSession(shared_ptr<ITcpClient> client) { };

    // Accepting new client error signal
    virtual void AcceptError() const { };

    // Server started signal
    virtual void ServerStarted() const { };

    // Binding tcp server
    // @port: local tcp port
    //
    // throw: error if fail binding
    void Start(unsigned port, unsigned max_clients);

private:
    SOCKET sock_;
};


#endif
