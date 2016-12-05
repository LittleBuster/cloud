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


FileTransfer::FileTransfer(const shared_ptr<ITcpClient> &client): client_(move(client))
{
}

void FileTransfer::OpenSend(const string &filename, unsigned long size)
{
    in_file_.open(filename, ios::binary);
    if (!in_file_.is_open())
        throw string("Can not open file for reading.");
    size_ = size;
}

void FileTransfer::OpenRecv(const string &localname, unsigned long size)
{
    out_file_.open(localname, ios::binary);
    if (!out_file_.is_open())
        throw string("Can not open file for writing.");
    size_ = size;
}

void FileTransfer::SendFile()
{
    char buf[DATA_SIZE];
    unsigned long count = size_ / DATA_SIZE;
    unsigned last_block = size_ % DATA_SIZE;

    for (unsigned long i = 0; i < count; i++) {
        in_file_.read(buf, DATA_SIZE);
        client_->Send(buf, DATA_SIZE);
    }

    char lastBuf[last_block];

    in_file_.read(lastBuf, last_block);
    client_->Send(lastBuf, last_block);
}

void FileTransfer::RecvFile()
{
    char buf[DATA_SIZE];
    unsigned long count = size_ / DATA_SIZE;
    unsigned last_block = size_ % DATA_SIZE;

    for (unsigned long i = 0; i < count; i++) {
        client_->Recv(buf, DATA_SIZE);
        out_file_.write(buf, DATA_SIZE);
    }

    char lastBuf[last_block];

    client_->Recv(lastBuf, last_block);
    out_file_.write(lastBuf, last_block);
}

void FileTransfer::Close()
{
    if (in_file_.is_open())
        in_file_.close();
    if (out_file_.is_open())
        out_file_.close();
}
