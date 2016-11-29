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

#include "filehash.h"
#include <string.h>
#include <openssl/sha.h>


string FileHash::hashToStr(const unsigned char *hash)
{
    string out = "";

    for (size_t i = 0; i < SHA512_DIGEST_LENGTH; i++) {
        char sym[4];

        sprintf(sym, "%02X", hash[i]);
        out += string(sym);
    }
    return out;
}

void FileHash::open(const string &filename)
{
    _file.open(filename);
}

string FileHash::generate()
{
    char buf[512];
    SHA512_CTX sha;
    unsigned char out[SHA512_DIGEST_LENGTH];

    SHA512_Init(&sha);

    while (!_file.eof()) {
        memset(buf, 0x00, 512);
        _file.read(buf, 512);
        SHA512_Update(&sha, buf, 512);
    }

    SHA512_Final(out, &sha);
    return hashToStr(out);
}

void FileHash::close()
{
    _file.close();
}
