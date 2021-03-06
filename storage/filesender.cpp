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

#include "filesender.h"


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

void FileSender::upload(const shared_ptr<ITcpClient> &client)
{
    char buf[DATA_SIZE];
    unsigned long count = size_ / DATA_SIZE;
    unsigned lastBlock = size_ % DATA_SIZE;

    for (unsigned long i = 0; i < count; i++) {
        file_.read(buf, DATA_SIZE);
        client->send(buf, DATA_SIZE);
    }

    shared_ptr<char> lastBuf(new char[lastBlock], default_delete<char[]>());

    file_.read(lastBuf.get(), lastBlock);
    client->send(lastBuf.get(), lastBlock);
}
