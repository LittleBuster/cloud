// Cloud: database test
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include <memory>
#include <iostream>

#include "../../base.h"


int main()
{
    auto fb = make_shared<FilesBase>();

    try {
        fb->open("files.db");
    }
    catch (const string &err) {
        cout << err << endl;
        return -1;
    }

    try {
        vector<File> files = fb->getFileList();

        for (const auto &f : files) {
            cout << f.filename << " " << f.size << endl;
        }
    } catch(const string &err) {
        cout << err << endl;
    }



    fb->close();
    return 0;
}
