//
// Created by Alex on 8/14/2023.
//

#include "Engine.h"

GameObject* Engine::CreateObject(uint64_t Id) {
    auto *obj = new GameObject(Id);
    GameObjectList.push_back(obj);
#ifdef ENGINE_DEBUG
    std::cout << "[Engine] New GameObject with id=" << Id << std::endl;
#endif
    return obj;
}