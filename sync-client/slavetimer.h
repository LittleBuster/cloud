/*
 * Cloud: sync client application
 *
 * Copyright (C) 2016-2017 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence 3
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#ifndef SLAVE_TIMER_H
#define SLAVE_TIMER_H

#include "timer.h"
#include "log.h"
#include "configs.h"
#include "filehash.h"
#include "tcpclient.h"
#include "session.h"
#include "timer.h"


using namespace std;
using namespace boost::asio;


/*
 * Downloading local files to server
 */
class SlaveTimer: public ITimer
{
public:
    SlaveTimer(const shared_ptr<ILog> &log, const shared_ptr<IConfigs> &cfg,
                const shared_ptr<ITcpClient> &client, const shared_ptr<ISession> &session);

    virtual void handler() override final;

    void start(unsigned delay);

    void stop() const;

private:
    const shared_ptr<ILog> log_;
    const shared_ptr<IConfigs> cfg_;
    const shared_ptr<ITcpClient> client_;
    const shared_ptr<ISession> session_;

    io_service io_;
    shared_ptr<deadline_timer> timer_;
    unsigned delay_;

    bool checkFile(const FileInfo &info) const;
    void deleteFilesAsNeeded(const vector<string> &files);
};


#endif
