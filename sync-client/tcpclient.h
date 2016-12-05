// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#include <memory>

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

using namespace std;


class ITcpClient
{
public:
    virtual void Connect(const string &ip, unsigned port)=0;
    virtual void Send(const void *data, size_t len) const=0;
    virtual void Recv(void *data, size_t len) const=0;
    virtual void Close(void) const=0;
};


class TcpClient: public ITcpClient
{
private:
    SOCKET client_;

public:
    TcpClient();

    TcpClient(SOCKET sock);

    /**
     * Connect to remote server
     * @ip: remote ip address
     * @port: remote socket port
     *
     * throw: error if fail connecting
     */
    void Connect(const string &ip, unsigned port);

    /**
     * Send data to server
     * @data: sending data
     * @len: data length
     *
     * throw: error if fail sending data
     */
    void Send(const void *data, size_t len) const;

    /**
     * Receive data from server
     * @data: receiving data
     * @len: data length
     *
     * throw: error if fail receiving data
     */
    void Recv(void *data, size_t len) const;

    /*
     * Close connection
     */
    void Close(void) const;
};


#endif
