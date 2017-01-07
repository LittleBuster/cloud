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


#ifndef CONFIGS_H
#define CONFIGS_H

#include <memory>
#include <fstream>

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


/*
 * Configs file decorator
 */
class ConfigsFile
{
public:
    ConfigsFile(const string &filename);
    ~ConfigsFile();
    string readString();
    bool isOpen() const;

private:
    ifstream file_;
};

class IConfigs
{
public:
    virtual const ServerCfg& getServerCfg(void) const=0;
    virtual const SyncCfg& getSyncCfg(void) const=0;
    virtual const BaseCfg& getUsersBaseCfg(void) const=0;
    virtual const BaseCfg& getFilesBaseCfg(void) const=0;
    virtual void load(const string &filename)=0;
};


class Configs: public IConfigs
{
public:
    inline const ServerCfg& getServerCfg(void) const { return sc_; }
    inline const SyncCfg& getSyncCfg(void) const { return syc_; }
    inline const BaseCfg& getUsersBaseCfg(void) const { return ubc_; }
    inline const BaseCfg& getFilesBaseCfg(void) const { return fbc_; }

    /**
     * Loading configs from json file
     * @filename: name of json file
     *
     * throw: errror if file not found or parsing fail
     */
    void load(const string &filename);

private:
    ServerCfg sc_;
    SyncCfg syc_;
    BaseCfg ubc_;
    BaseCfg fbc_;
};


#endif
