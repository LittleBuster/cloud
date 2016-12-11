// Cloud: storage application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include <functional>
#include <thread>

#include "tcpserver.h"


void TcpServer::Start(unsigned port, unsigned max_clients)
{
    int ret_val;
    struct sockaddr_in sock_addr;

#ifdef WIN32
    WSADATA wsaData;
    WORD version_wanted = MAKEWORD(1, 1);

    if (WSAStartup(version_wanted, &wsaData) != 0)
        throw string("Fail WSA init.");
#endif

    sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_ == INVALID_SOCKET)
        throw string("Fail Socket init.");

    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = INADDR_ANY;
    sock_addr.sin_port = htons(port);

    ret_val = bind(sock_, reinterpret_cast<struct sockaddr *>(&sock_addr), sizeof(sock_addr));
    if (ret_val == SOCKET_ERROR)
        throw string("Fail binding server.");

    ret_val = listen(sock_, max_clients);
    if (ret_val == SOCKET_ERROR)
        throw string("Fail starting listening.");

    ServerStarted();

    for (;;) {
        SOCKET client_socket = accept(sock_, NULL, NULL);

        if (client_socket == SOCKET_ERROR) {
            AcceptError();
            continue;
        }

        auto client = make_shared<TcpClient>(client_socket);
        thread th(bind(&TcpServer::NewSession, this, client));
        th.detach();
    }

    if (sock_ != INVALID_SOCKET) {
        ::shutdown(sock_, 1);
        ::close(sock_);
    }
#ifdef WIN32
    if (WSACleanup() == SOCKET_ERROR) {
        if (WSAGetLastError() == WSAEINPROGRESS) {
#ifndef _WIN32_WCE
            WSACancelBlockingCall();
#endif
            WSACleanup();
        }
    }
#endif
}
