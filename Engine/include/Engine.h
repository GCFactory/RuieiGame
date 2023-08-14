//
// Created by Alex on 8/14/2023.
//
#pragma once

#ifndef RUEIEGAME_ENGINE_H
#define RUEIEGAME_ENGINE_H

#include <iostream>
#include <vector>

#include "GameObject.h"

class Engine {
protected:
    std::vector<GameObject*>  GameObjectList;
public:
    GameObject* CreateObject(uint64_t Id);
    void UpdateState();
};
#endif //RUEIEGAME_ENGINE_H
