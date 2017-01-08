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


#include <iostream>
#include <memory>

#include "base.h"


typedef struct {
    string passwd;
    bool result;
} VerifyData;

typedef struct {
    shared_ptr<File> file;
    bool result;
} VerifyFileData;


static int ExistsCb(void *data, int argc, char **argv, char **col_name)
{
    bool *exists = reinterpret_cast<bool*>(data);

    if (argc != 0)
        *exists = true;
    else
        *exists = false;
    return 0;
}

static int VerifyCb(void *data, int argc, char **argv, char **col_name)
{
    VerifyData *verify = reinterpret_cast<VerifyData*>(data);

    if (string(argv[2]) != verify->passwd)
        verify->result = false;
    else
        verify->result = true;
    return 0;
}

static int PrivCb(void *data, int argc, char **argv, char **col_name)
{
    unsigned *priv = reinterpret_cast<unsigned*>(data);
    *priv = static_cast<unsigned>(atoi(argv[3]));
    return 0;
}


void UsersBase::open(const string &filename)
{
    int ret_val;

    ret_val = sqlite3_open(filename.c_str(), &base_);
    if(ret_val)
        throw string("Can not connect to database.");
}

bool UsersBase::exists(const User &user)
{
    int ret_val;
    bool exists;
    char *err_msg = 0;

    string sql = "SELECT * FROM users WHERE name=\"" + user.name + "\"";

    ret_val = sqlite3_exec(base_, sql.c_str(), ExistsCb, reinterpret_cast<void*>(&exists), &err_msg);
    if (ret_val != SQLITE_OK) {
        string err(err_msg);
        sqlite3_free(err_msg);
        throw string("UsersBase exists: " + err);
    }
    return exists;
}

unsigned UsersBase::getUserPriv(const User &user)
{
    int ret_val;
    unsigned priv;
    char *err_msg = 0;

    string sql = "SELECT * FROM users WHERE name=\"" + user.name + "\"";

    ret_val = sqlite3_exec(base_, sql.c_str(), PrivCb, reinterpret_cast<void*>(&priv), &err_msg);
    if (ret_val != SQLITE_OK) {
        string err(err_msg);
        sqlite3_free(err_msg);
        throw string("UsersBase priv: " + err);
    }
    return priv;
}

bool UsersBase::verify(const User &user)
{
    int ret_val;
    char *err_msg = 0;
    VerifyData data;

    data.passwd = user.passwd;
    string sql = "SELECT * FROM users WHERE name=\"" + user.name + "\"";

    ret_val = sqlite3_exec(base_, sql.c_str(), VerifyCb, reinterpret_cast<void*>(&data), &err_msg);
    if (ret_val != SQLITE_OK) {
        string err(err_msg);
        sqlite3_free(err_msg);
        throw string("UsersBase verify: " + err);
    }
    return data.result;
}

void UsersBase::close()
{
    sqlite3_close(base_);
}

void FilesBase::open(const string &filename)
{
    int ret_val;

    ret_val = sqlite3_open(filename.c_str(), &base_);
    if(ret_val)
        throw string("Can not connect to database.");
}

void FilesBase::addFile(const File &file)
{
    int ret_val;
    char *err_msg = 0;

    string sql = "INSERT INTO files(name,size,modify,hash) VALUES (\"" + file.filename
                 + "\", " + to_string(file.size) + ", \"" + file.modify + "\", \""
                 + file.hash + "\")";

    ret_val = sqlite3_exec(base_, sql.c_str(), nullptr, nullptr, &err_msg);
    if (ret_val != SQLITE_OK) {
        string err(err_msg);
        sqlite3_free(err_msg);
        throw string("FilesBase addfile: " + err);
    }
}

bool FilesBase::exists(const File &file)
{
    int ret_val;
    bool exists;
    char *err_msg = 0;

    string sql = "SELECT * FROM files WHERE name=\"" + file.filename + "\"";

    ret_val = sqlite3_exec(base_, sql.c_str(), ExistsCb, reinterpret_cast<void*>(&exists), &err_msg);
    if (ret_val != SQLITE_OK) {
        string err(err_msg);
        sqlite3_free(err_msg);
        throw string("FilesBase exists: " + err);
    }
    return exists;
}

static int VerifyFileCb(void *data, int argc, char **argv, char **col_name)
{
    VerifyFileData *verify = reinterpret_cast<VerifyFileData*>(data);

    if (string(argv[3]) == verify->file->modify && string(argv[4]) == verify->file->hash)
        verify->result = true;
    else
        verify->result = false;
    return 0;
}

bool FilesBase::verify(const File &file)
{
    int ret_val;
    char *err_msg = 0;
    VerifyFileData data;

    data.file = make_shared<File>(file);
    string sql = "SELECT * FROM files WHERE name=\"" + file.filename + "\"";

    ret_val = sqlite3_exec(base_, sql.c_str(), VerifyFileCb, reinterpret_cast<void*>(&data), &err_msg);
    if (ret_val != SQLITE_OK) {
        string err(err_msg);
        sqlite3_free(err_msg);
        throw string("FilesBase verify: " + err);
    }
    return data.result;
}

static int FileListCb(void *data, int argc, char **argv, char **col_name)
{
    File file;
    vector<File> *files = reinterpret_cast<vector<File> *>(data);

    file.filename = string(argv[1]);
    file.size = static_cast<unsigned long>(atoi(argv[2]));
    file.modify = string(argv[3]);
    file.hash = string(argv[4]);

    files->push_back(file);
    return 0;
}

vector<File> FilesBase::getFileList()
{
    int ret_val;
    char *err_msg = 0;
    vector<File> files;

    string sql = "SELECT * FROM files";

    ret_val = sqlite3_exec(base_, sql.c_str(), FileListCb, reinterpret_cast<void*>(&files), &err_msg);
    if (ret_val != SQLITE_OK) {
        string err(err_msg);
        sqlite3_free(err_msg);
        throw string("FilesBase filelist: " + err);
    }
    return files;
}

void FilesBase::close()
{
    sqlite3_close(base_);
}
