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


#ifndef NETWORK_H
#define NETWORK_H


enum CmdCodes {
    CMD_SEND_FILE = 100,
    CMD_RECV_FILE = 101,
    CMD_LOGIN = 102,
    CMD_EXIT = 103
};

enum AnswCodes {
    ANSW_NOTHING,
    ANSW_NEED_UPLOAD,
    ANSW_LOGIN_OK
};


typedef struct {
    unsigned code;
} Command;


#endif
