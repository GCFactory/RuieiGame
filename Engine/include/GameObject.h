//
// Created by Alex on 8/13/2023.
//


#ifndef RUEIEGAME_GAMEOBJECT_H
#define RUEIEGAME_GAMEOBJECT_H

#include "EngineBase.h"

class GameObject {
protected:
    uint64_t Id;
    Pointf Position;
public:
    GameObject(uint64_t _Id);

    uint64_t GetId();

    Pointf GetPosition();
    void SetPosition(float _x, float _y);
    void SetPositionX(float newCoord);
    void SetPositionY(float newCoord);
private:
};

#endif //RUEIEGAME_GAMEOBJECT_H