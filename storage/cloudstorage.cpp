// Cloud: storage application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#include <iostream>

#include "cloudstorage.h"
#include "filetransfer.h"
#include "network.h"
#include "session.h"


CloudStorage::CloudStorage(const shared_ptr<IConfigs> &cfg, const shared_ptr<ILog> &log, const shared_ptr<IUsersBase> &users_base):
                           cfg_(move(cfg)), log_(move(log)), users_base_(move(users_base))
{
}

void CloudStorage::NewSession(shared_ptr<ITcpClient> client)
{
    Command cmd;
    auto session = make_shared<Session>(client, cfg_, users_base_);

    while (true) {
        try {
            client->Recv(&cmd, sizeof(cmd));
        }
        catch (const string &err) {
             log_->Local("Receiving command: " + err, LOG_ERROR);
            return;
        }

        switch (cmd.code) {
            case CMD_LOGIN: {
                try {
                    session->OpenNewSession();
                }
                catch (const string &err) {
                    log_->Local("Checking user: " + err, LOG_ERROR);
                    return;
                }
                break;
            }
            case CMD_SEND_FILE: {
                FileInfo info;
                const auto &syc = cfg_->GetSyncCfg();

                cout << "Receiving new file..." << endl;
                try {
                    client->Recv(&info, sizeof(FileInfo));

                    FileReceiver fr(syc.path + string(info.filename), info.size);
                    fr.Download(client);
                }
                catch (const string &err) {
                    log_->Local(err, LOG_ERROR);
                }
                cout << info.filename << endl
                     << info.size << endl
                     << info.modify_time << endl
                     << info.hash << endl;
                break;
            }

            case CMD_RECV_FILE: {
                break;
            }

            case CMD_EXIT: {
                cout << "Client disconnected." << endl;
                return;
                break;
            }
        }
    }
}

void CloudStorage::AcceptError() const
{

}

void CloudStorage::ServerStarted() const
{

}
