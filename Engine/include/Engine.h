//
// Created by Alex on 8/14/2023.
//

#ifndef RUEIEGAME_ENGINE_H
#define RUEIEGAME_ENGINE_H

#pragma once

#include "Global.h"
#include "GameObject.h"


class Engine final{
protected:
    std::vector<GameObject *> GameObjectList;
public:
    Engine();
    void Initilaze();

    void UpdateState();

    void HandleWindowEvent(RenderWindow *window, Event event);
};

#endif //RUEIEGAME_ENGINE_H
