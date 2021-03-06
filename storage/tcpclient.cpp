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


#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "tcpclient.h"


TcpClient::TcpClient()
{
}

TcpClient::TcpClient(SOCKET sock)
{
    client_ = sock;
}

void TcpClient::connect(const string &ip, unsigned port)
{
    int ret_val;
    struct sockaddr_in sock_addr;

#ifdef _WIN32
    WSADATA wsaData;
    WORD version_wanted = MAKEWORD(1, 1);

    if (WSAStartup(version_wanted, &wsaData) != 0)
        throw string("Fail WSA init.");
#endif

    memset(&sock_addr, 0x00, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    sock_addr.sin_port = htons(port);

    client_ = socket(AF_INET, SOCK_STREAM, 0);
    if (client_ == INVALID_SOCKET)
        throw string("Can not create client socket.");

    ret_val = ::connect(client_, reinterpret_cast<struct sockaddr*>(&sock_addr), sizeof(sock_addr));
    if (ret_val == SOCKET_ERROR)
        throw string("Can not connect to server.");
}

void TcpClient::send(const void *data, size_t len) const
{
    int ret_val = 0;

    for (;;) {
        ret_val = ::send(client_, reinterpret_cast<const char*>(data), len, 0);
        if (ret_val == SOCKET_ERROR)
            throw string("Fail sending data.");

        if (ret_val == static_cast<int>(len))
            break;
    }
}

void TcpClient::recv(void *data, size_t len) const
{
    int bytes;

    bytes = ::recv(client_, reinterpret_cast<char *>(data), len, 0);
    if ((bytes == 0) || (bytes == SOCKET_ERROR))
        throw string("Fail receiving data.");
}

void TcpClient::close() const
{
    if (client_ != 0) {
        ::shutdown(client_, 1);
#ifdef _WIN32
        closesocket(client_);
        if (WSACleanup() == SOCKET_ERROR) {
            if (WSAGetLastError() == WSAEINPROGRESS) {
#ifndef _WIN32_WCE
                WSACancelBlockingCall();
#endif
                WSACleanup();
            }
        }
#else
        ::close(client_);
#endif
    }
}
