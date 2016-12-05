// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef FILE_TRANSFER_H_
#define FILE_TRANSFER_H_

#include <memory>
#include <fstream>

#include "tcpclient.h"


using namespace std;

#define DATA_SIZE 512


class IFileTransfer
{
public:
    virtual void OpenSend(const string &filename, unsigned long size)=0;
    virtual void OpenRecv(const string &localname, unsigned long size)=0;
    virtual void SendFile()=0;
    virtual void RecvFile()=0;
    virtual void Close()=0;
};


class FileTransfer: public IFileTransfer
{
private:
    const shared_ptr<ITcpClient> client_;
    ifstream in_file_;
    ofstream out_file_;
    unsigned long size_;

public:
    FileTransfer(const shared_ptr<ITcpClient> &client);

    void OpenSend(const string &filename, unsigned long size);

    void OpenRecv(const string &localname, unsigned long size);

    void SendFile();

    void RecvFile();

    void Close();
};


#endif
