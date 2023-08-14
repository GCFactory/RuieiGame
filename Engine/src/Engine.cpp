//
// Created by Alex on 8/14/2023.
//

#ifdef DEBUG
#define ENGINE_DEBUG
#endif

#include "Engine.h"
#include "TextureList.h"
#include "TextureManager.h"

void Engine::Initilaze() {
    int error = 0;
    for (uint32_t i = 1; i <= TextureList.size(); i++) {
#ifdef ENGINE_DEBUG
        std::cout << "[Engine] Try to load texture '" << TextureList[i] << "'" std::endl;
#endif
        error = TextureManager::LoadTextureFromFile(i, TextureList[i]);
        if (error != 0) {
            throw std::exception("[Engine] Failed to load texture");
        }
    }
}