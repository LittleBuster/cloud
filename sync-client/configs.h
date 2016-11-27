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

#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include <memory>

using namespace std;


typedef struct {
    string ip;
    unsigned port;
} ServerCfg;

typedef struct {
    string path;
    unsigned interval;
} SyncCfg;


class IConfigs
{
public:
    virtual const ServerCfg& getServerCfg(void) const=0;
    virtual const SyncCfg& getSyncCfg(void) const=0;
    virtual void load(const string &filename)=0;
};


class Configs: public IConfigs
{
private:
    ServerCfg sc;
    SyncCfg syc;

    string readString(ifstream &is) const;

    int readInt(ifstream &is) const;

public:
    inline const ServerCfg& getServerCfg(void) const { return sc; }

    inline const SyncCfg& getSyncCfg(void) const { return syc; }

    /**
     * Loading configs from json file
     * @filename: name of json file
     *
     * throw: errror if file not found or parsing fail
     */
    void load(const string &filename);
};


#endif
