#include <iostream>

#include "cloudstorage.h"
#include "filetransfer.h"


CloudStorage::CloudStorage(const shared_ptr<IConfigs> &cfg, const shared_ptr<ILog> &log):
                           cfg_(move(cfg)), log_(move(log))
{

}

void CloudStorage::NewSession(shared_ptr<ITcpClient> client)
{
    Command cmd;

    while (true) {
        try {
            client->Recv(&cmd, sizeof(Command));
        }
        catch (const string &err) {
             log_->Local(err, LOG_ERROR);
            return;
        }

        switch (cmd.code) {
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
