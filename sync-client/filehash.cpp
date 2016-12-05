// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <string.h>

#include <openssl/sha.h>

#include "filehash.h"


string FileHash::HashToStr(const unsigned char *hash)
{
    string out = "";

    for (size_t i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        char sym[4];

        sprintf(sym, "%02X", hash[i]);
        out += string(sym);
    }
    return out;
}

FileHash::FileHash(const string &filename)
{
    file_.open(filename);
}

FileHash::~FileHash()
{
    file_.close();
}

string FileHash::Generate()
{
    char buf[512];
    SHA512_CTX sha;
    unsigned char out[SHA512_DIGEST_LENGTH];

    SHA512_Init(&sha);

    while (!file_.eof()) {
        memset(buf, 0x00, 512);
        file_.read(buf, 512);
        SHA512_Update(&sha, buf, 512);
    }

    SHA512_Final(out, &sha);
    return HashToStr(out);
}
