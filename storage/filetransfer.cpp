// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include "filetransfer.h"


FileSender::FileSender(const string &filename, unsigned long size)
{
    file_.open(filename, ios::binary);
    if (!file_.is_open())
        throw string("Can not open file for reading.");
    size_ = size;
}

FileSender::~FileSender()
{
    if (file_.is_open())
        file_.close();
}

void FileSender::Upload(const shared_ptr<ITcpClient> &client)
{
    char buf[DATA_SIZE];
    unsigned long count = size_ / DATA_SIZE;
    unsigned last_block = size_ % DATA_SIZE;

    for (unsigned long i = 0; i < count; i++) {
        file_.read(buf, DATA_SIZE);
        client->Send(buf, DATA_SIZE);
    }

    char last_buf[last_block];

    file_.read(last_buf, last_block);
    client->Send(last_buf, last_block);
}

FileReceiver::FileReceiver(const string &localfile, unsigned long size)
{
    file_.open(localfile, ios::binary);
    if (!file_.is_open())
        throw string("Can not open file for writing.");
    size_ = size;
}

FileReceiver::~FileReceiver()
{
    if (file_.is_open())
        file_.close();
}

void FileReceiver::Download(const shared_ptr<ITcpClient> &client)
{
    char buf[DATA_SIZE];
    unsigned long count = size_ / DATA_SIZE;
    unsigned last_block = size_ % DATA_SIZE;

    for (unsigned long i = 0; i < count; i++) {
        client->Recv(buf, DATA_SIZE);
        file_.write(buf, DATA_SIZE);
    }

    char last_buf[last_block];

    client->Recv(last_buf, last_block);
    file_.write(last_buf, last_block);
}
