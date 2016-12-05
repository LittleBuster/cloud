// Cloud: sync client application
//
// Copyright (C) 2016 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.


#ifndef LOG_H_
#define LOG_H_


#include <string>
#include <memory>

using namespace std;


typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_INFORMATION
} LogType;


class ILog
{
public:
    virtual void SetLogFile(const string &filepath) = 0;
    virtual void Local(const string &message, const LogType log_type) = 0;
};


class Log: public ILog
{
public:
    explicit Log();

    /*
     * Set path for saving log data in local file
     */
    inline void SetLogFile(const string &filepath) { log_path_ = filepath; }

    /**
     * Saving log data in local file
     * @message: log message
     * @logType: message type
     *
     * throw: error if fail access to file
     */
    void Local(const string &message, const LogType log_type);

private:
    string log_path_;
    using ILog::SetLogFile;

    /**
     * Create log string for writing to file
     * @msg: logging message
     * @type: log message type
     *
     * returns full log string width datetime and type
     */
    string MakeLogMsg(const string &msg, const LogType type) const;
};


#endif
