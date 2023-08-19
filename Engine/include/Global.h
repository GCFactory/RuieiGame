//
// Created by Alex on 8/19/2023.
//

#ifndef RUEIEGAME_GLOBAL_H
#define RUEIEGAME_GLOBAL_H

#pragma once

#include "Global/GlobalDefinitions.h"
#include "Global/GlobalMath.h"
#include "Enums/ErrorID.h"
#include "Enums/LogLevel.h"

#define NOP []() {}

#define CLEAR_VECTOR(V) for (auto it : V) {delete it;}; V.clear();
#define CLEAR_MAP(M) for (auto it : M) {delete it.second;}; M.clear();

// extern objects
class Logger;
class Engine;

extern Logger* g_Logger;
extern Engine* g_Engine;

#endif //RUEIEGAME_GLOBAL_H
