//
// Created by Alex on 8/19/2023.
//

#ifndef RUEIEGAME_LOGLEVEL_H
#define RUEIEGAME_LOGLEVEL_H


#pragma once

// the importance of the log output. 0 is the highest (None)
// and should never be used to log messages (would have no effect)
enum class LogLevel {
    None,
    Error,
    Warning,
    Info,
    Debug,
    Verbose,
};

#endif //RUEIEGAME_LOGLEVEL_H
