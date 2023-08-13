// Game.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"

class Engine {
protected:
    std::vector<GameObject*>  GameObjectList;
public:
    GameObject* CreateObject(uint64_t Id) {
        GameObject *obj = new GameObject(Id);
        GameObjectList.push_back(obj);
#ifdef ENGINE_DEBUG
        std::cout << "[Engine] New GameObject with id=" << Id << std::endl;
#endif
        return obj;
    }
};