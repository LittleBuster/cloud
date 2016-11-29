/* Cloud: sync client application
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#ifndef __FILE_TRANSFER_H__
#define __FILE_TRANSFER_H__

#include "tcpclient.h"
#include <memory>
#include <fstream>

using namespace std;

#define DATA_SIZE 512


class IFileTransfer
{
public:
    virtual void openSend(const string &filename, unsigned long size)=0;
    virtual void openRecv(const string &localname, unsigned long size)=0;
    virtual void sendFile()=0;
    virtual void recvFile()=0;
    virtual void close()=0;
};


class FileTransfer: public IFileTransfer
{
private:
    const shared_ptr<ITcpClient> _client;
    ifstream _inFile;
    ofstream _outFile;
    unsigned long _size;

public:
    FileTransfer(const shared_ptr<ITcpClient> &client);

    void openSend(const string &filename, unsigned long size);

    void openRecv(const string &localname, unsigned long size);

    void sendFile();

    void recvFile();

    void close();
};


#endif
