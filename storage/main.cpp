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


#include "app.h"
#include "log.h"
#include "configs.h"
#include "cloudstorage.h"
#include "base.h"


int main()
{
    auto log = make_shared<Log>();
    auto cfg = make_shared<Configs>();
    auto users_base = make_shared<UsersBase>();
    auto files_base = make_shared<FilesBase>();
    auto storage = make_shared<CloudStorage>(cfg, log, users_base, files_base);
    auto app = make_shared<App>(log, cfg, storage);

    return app->start();
}
