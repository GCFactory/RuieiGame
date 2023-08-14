//
// Created by Alex on 8/14/2023.
//

#ifndef RUEIEGAME_ENGINE_H
#define RUEIEGAME_ENGINE_H

#include <iostream>
#include <vector>

#include "GameObject.h"

class Engine {
protected:
    std::vector<GameObject *> GameObjectList;
public:
    void Initilaze();

    void UpdateState();
};

#endif //RUEIEGAME_ENGINE_H
