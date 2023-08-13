//
// Created by Alex on 8/13/2023.
//

#ifndef RUEIEGAME_TEXTUREMANAGER_H
#define RUEIEGAME_TEXTUREMANAGER_H

#include "Errors.h"
#include "SFML/Graphics.hpp"

class TextureManager {
protected:
    std::vector<sf::Texture*> TextureList;
public:
    static int LoadTextureFromFile(std::string Path);
};

#endif //RUEIEGAME_TEXTUREMANAGER_H
