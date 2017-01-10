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


#include "filereceiver.h"


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

void FileReceiver::download(const shared_ptr<ITcpClient> &client)
{
    char buf[DATA_SIZE];
    unsigned long count = size_ / DATA_SIZE;
    unsigned lastBlock = size_ % DATA_SIZE;

    for (unsigned long i = 0; i < count; i++) {
        client->recv(buf, DATA_SIZE);
        file_.write(buf, DATA_SIZE);
    }

    shared_ptr<char> lastBuf(new char[lastBlock], default_delete<char[]>());

    client->recv(lastBuf.get(), lastBlock);
    file_.write(lastBuf.get(), lastBlock);
}
