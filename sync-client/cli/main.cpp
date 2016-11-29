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

#include "app.h"
#include "log.h"
#include "configs.h"
#include "filehash.h"
#include "filewatch.h"
#include "tcpclient.h"
#include "filetransfer.h"


int main()
{
    auto log = make_shared<Log>();
    auto cfg = make_shared<Configs>();
    auto fhash = make_shared<FileHash>();
    auto client = make_shared<TcpClient>();
    auto ftransfer = make_shared<FileTransfer>(client);
    auto fwatch = make_shared<FileWatch>(log, cfg, fhash, ftransfer, client);
    auto app = make_shared<App>(log, cfg, fwatch);

    return app->start();
}
