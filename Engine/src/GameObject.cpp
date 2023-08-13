//
// Created by Alex on 8/13/2023.
//

#include "EngineBase.h"
#include "GameObject.h"

GameObject::GameObject(uint64_t _Id) : Id(_Id) {

}

uint64_t GameObject::GetId() {
    return Id;
}

Pointf GameObject::GetPosition() {
    return this->Position;
}
void GameObject::SetPosition(float _x, float _y) {
    Position.x = _x;
    Position.y = _y;
#ifdef ENGINE_DEBUG
    std::cout << "[GameObject-" << Id << "] Set new position (" <<  _x << ", " << _y << ")" << std::endl;
#endif
}
void GameObject::SetPositionX(float newCoord) {
    Position.x = newCoord;
#ifdef ENGINE_DEBUG
    std::cout << "[GameObject-" << Id << "] Set new position (" <<  newCoord << ", " << Position.y << ")" << std::endl;
#endif
}
void GameObject::SetPositionY(float newCoord) {
    Position.y = newCoord;
#ifdef ENGINE_DEBUG
    std::cout << "[GameObject-" << Id << "] Set new position (" <<  Position.x << ", " << newCoord << ")" << std::endl;
#endif
}