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


#ifndef FILE_RECEIVER_H
#define FILE_RECEIVER_H


#include <memory>
#include <fstream>

#include "tcpclient.h"

using namespace std;

#define DATA_SIZE 512


class FileReceiver
{
public:
    explicit FileReceiver(const string &localfile, unsigned long size);

    ~FileReceiver();

    void download(const shared_ptr<ITcpClient> &client);

private:
    ofstream file_;
    unsigned long size_;
};


#endif
