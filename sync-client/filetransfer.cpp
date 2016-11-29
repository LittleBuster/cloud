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

#include "filetransfer.h"


FileTransfer::FileTransfer(const shared_ptr<ITcpClient> &client): _client(move(client))
{
}

void FileTransfer::openSend(const string &filename, unsigned long size)
{
    _inFile.open(filename, ios::binary);
    if (!_inFile.is_open())
        throw string("Can not open file for reading.");
    _size = size;
}

void FileTransfer::openRecv(const string &localname, unsigned long size)
{
    _outFile.open(localname, ios::binary);
    if (!_outFile.is_open())
        throw string("Can not open file for writing.");
    _size = size;
}

void FileTransfer::sendFile()
{
    char buf[DATA_SIZE];
    unsigned long count = _size / DATA_SIZE;
    unsigned lastBlock = _size % DATA_SIZE;

    for (unsigned long i = 0; i < count; i++) {
        _inFile.read(buf, DATA_SIZE);
        _client->send(buf, DATA_SIZE);
    }

    char lastBuf[lastBlock];

    _inFile.read(lastBuf, lastBlock);
    _client->send(lastBuf, lastBlock);
}

void FileTransfer::recvFile()
{
    char buf[DATA_SIZE];
    unsigned long count = _size / DATA_SIZE;
    unsigned lastBlock = _size % DATA_SIZE;

    for (unsigned long i = 0; i < count; i++) {
        _client->recv(buf, DATA_SIZE);
        _outFile.write(buf, DATA_SIZE);
    }

    char lastBuf[lastBlock];

    _client->recv(lastBuf, lastBlock);
    _outFile.write(lastBuf, lastBlock);
}

void FileTransfer::close()
{
    if (_inFile.is_open())
        _inFile.close();
    if (_outFile.is_open())
        _outFile.close();
}
