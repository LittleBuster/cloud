// Cloud: storage application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef CONFIGS_H_
#define CONFIGS_H_

#include <memory>

using namespace std;


typedef struct {
    unsigned port;
    unsigned max_users;
} ServerCfg;

typedef struct {
    string path;
} SyncCfg;

typedef struct {
    string path;
} BaseCfg;


class IConfigs
{
public:
    virtual const ServerCfg& GetServerCfg(void) const=0;
    virtual const SyncCfg& GetSyncCfg(void) const=0;
    virtual const BaseCfg& GetUsersBaseCfg(void) const=0;
    virtual const BaseCfg& GetFilesBaseCfg(void) const=0;
    virtual void Load(const string &filename)=0;
};


class Configs: public IConfigs
{
public:
    inline const ServerCfg& GetServerCfg(void) const { return sc_; }

    inline const SyncCfg& GetSyncCfg(void) const { return syc_; }

    inline const BaseCfg& GetUsersBaseCfg(void) const { return ubc_; }

    inline const BaseCfg& GetFilesBaseCfg(void) const { return fbc_; }

    /**
     * Loading configs from json file
     * @filename: name of json file
     *
     * throw: errror if file not found or parsing fail
     */
    void Load(const string &filename);

private:
    ServerCfg sc_;
    SyncCfg syc_;
    BaseCfg ubc_;
    BaseCfg fbc_;

    string ReadString(ifstream &is) const;

    int ReadInt(ifstream &is) const;
};


#endif
