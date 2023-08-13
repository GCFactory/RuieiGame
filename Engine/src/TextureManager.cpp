//
// Created by Alex on 8/13/2023.
//
#include "TextureManager.h"

#include "SFML/Graphics/Texture.hpp"

int TextureManager::LoadTextureFromFile(std::string Path){
    sf::Texture t;
    t.setSmooth(true);
    if(!t.loadFromFile(Path)) {
        return ERROR_TEXTURE_NOT_LOADED;
    } else {
        return 0;
    }
}