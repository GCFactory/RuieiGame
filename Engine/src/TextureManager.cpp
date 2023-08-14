//
// Created by Alex on 8/13/2023.
//
#include "SFML/Graphics/Texture.hpp"

#include "TextureManager.h"

int TextureManager::LoadTextureFromFile(uint64_t Key, const std::string& Path) {
    auto *t = new sf::Texture();
    t->setSmooth(true);
    if (TextureManager::TextureList.contains(Key)) {
        return ERROR_TEXTURE_ALREADY_DECLARED;
    } else {
        if (!t->loadFromFile(Path)) {
            return ERROR_TEXTURE_NOT_LOADED;
        } else {
#ifdef ENGINE_DEBUG
    std::cout << "[TextureManager] New texture loaded with id=" << Key << std::endl;
#endif
            TextureManager::TextureList.insert_or_assign(Key, t);
            return 0;
        }
    }
}