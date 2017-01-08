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
    auto ub = make_shared<UsersBase>();

    try {
        ub->Open("../../../users.db");
    }
    catch (const string &err) {
        cout << err << endl;
        return -1;
    }

    User user;
    user.name = "adm";
    user.passwd = "123";

    try {
        if (ub->Exists(user))
            cout << "[PASSED] Exists user." << endl;
        else
            cout << "[ERROR] Exists user." << endl;
    }
    catch (const string &err) {
        cout << "[ERROR] Exists user." << endl;
        cout << err << endl;
    }

    try {
        if (ub->Verify(user))
            cout << "[PASSED] Verify user." << endl;
        else
            cout << "[ERROR] Verify user." << endl;
    }
    catch (const string &err) {
        cout << "[ERROR] Verify user." << endl;
        cout << err << endl;
    }

    user.name = "test2";
    user.passwd = "123";

    try {
        if (!ub->Exists(user))
            cout << "[PASSED] Not exists user." << endl;
        else
            cout << "[ERROR] Not exists user." << endl;
    }
    catch (const string &err) {
        cout << "[ERROR] Not exists user." << endl;
        cout << err << endl;
    }

    user.name = "adm";
    user.passwd = "321";
    try {
        if (!ub->Verify(user))
            cout << "[PASSED] Not verify user." << endl;
        else
            cout << "[ERROR] Not verify user." << endl;
    }
    catch (const string &err) {
        cout << "[ERROR] Not verify user." << endl;
        cout << err << endl;
    }

    ub->Close();
    return 0;
}
