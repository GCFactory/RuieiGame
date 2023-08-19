//
// Created by Alex on 8/19/2023.
//

#ifndef RUEIEGAME_LOGGER_H
#define RUEIEGAME_LOGGER_H

#pragma once

#include "Global.h"
#include "Enums/LogLevel.h"

class Logger final {
public:
    Logger();
    void logError(const std::string& source, const std::string& message) const;
    void logWarning(const std::string& source, const std::string& message) const;
    void logInfo(const std::string& source, const std::string& message) const;
    // logs the message with importance level. The source should describe the calling class and/or method.
    void log(LogLevel level, const std::string& source, const std::string& message) const;
    // sets the log level to 'level'. The log will only output messages, that have importance 'level' or higher.
    // if the log level is set to 'None', the log won't output anything.
    void setLogLevel(LogLevel level);
    LogLevel getLogLevel() const;

private:
    std::ostream *m_targetStream;
    LogLevel m_logLevel;

    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    const std::string DEFAULT = "\033[0m";
};

#endif //RUEIEGAME_LOGGER_H
