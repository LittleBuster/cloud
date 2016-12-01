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

#include "filewatch.h"
#include <vector>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>

namespace fs = boost::filesystem;


FileWatch::FileWatch(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg,
                     const shared_ptr<IFileHash> &fhash,
                     const shared_ptr<ITcpClient> &client,
                     const shared_ptr<IFileTransfer> &ftransfer):
                     _log(move(log)), _cfg(move(cfg)), _fhash(move(fhash)),
                     _client(move(client)), _ftransfer(move(ftransfer))
{
}

void FileWatch::handler()
{
    const auto &syc = _cfg->getSyncCfg();    
    vector<boost::filesystem::path> files;

    fs::path path(syc.path);
    copy(fs::directory_iterator(path), fs::directory_iterator(), back_inserter(files));

    for (const fs::path &file : files) {
        if (!fs::is_directory(file)) {
            cout << file.string() << endl;
            _fhash->open(file.string());
            cout << _fhash->generate() << endl << endl;
            _fhash->close();
        }
    }
}
