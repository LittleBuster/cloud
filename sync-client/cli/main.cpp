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
#include "filewatch.h"
#include <memory>

using namespace std;


int main()
{
    auto log = make_shared<Log>();
    auto cfg = make_shared<Configs>();
    auto fileWatch = make_shared<FileWatch>(log, cfg);
    auto app = make_shared<App>(log, cfg, fileWatch);

    return app->start();
}
