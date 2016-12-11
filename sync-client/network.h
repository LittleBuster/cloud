// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef NETWORK_H_
#define NETWORK_H_


enum CmdCodes {
    CMD_SEND_FILE,
    CMD_RECV_FILE,
    CMD_CHECK_USER,
    CMD_LOGIN,
    CMD_EXIT
};

enum AnswCodes {
    ANSW_NOTHING,
    ANSW_NEED_UPLOAD,
    ANSW_LOGIN_OK
};


typedef struct {
    unsigned int code;
} Command;


#endif
