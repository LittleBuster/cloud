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


#ifndef FILES_BASE_H
#define FILES_BASE_H

#include <vector>
#include <string>

#include <sqlite3.h>

using namespace std;


typedef struct {
    unsigned long size;
    string hash;
    string filename;
    string modify;
} File;


class IFilesBase
{
public:
    virtual void open(const string &filename)=0;
    virtual void addFile(const File &file)=0;
    virtual void removeFile(const File &file)=0;
    virtual bool exists(const File &file)=0;
    virtual bool verify(const File &file)=0;
    virtual vector<File> getFileList()=0;
    virtual void close()=0;
};


class FilesBase: public IFilesBase
{
public:
    /**
     * Loading database with files
     * @filename: path to database
     */
    void open(const string &filename);

    /*
     * Adding new file
     */
    void addFile(const File &file);

    /*
     * Removing file
     */
    void removeFile(const File &file);

    /*
     * Existing file in base
     */
    bool exists(const File &file);

    /*
     * Compare file info
     */
    bool verify(const File &file);

    /*
     * Getting local file list
     */
    vector<File> getFileList();

    /*
     * Closing base
     */
    void close();

private:
    sqlite3 *base_;
};


#endif
