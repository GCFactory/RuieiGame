//
// Created by Alex on 8/13/2023.
//

#ifndef RUEIEGAME_TEXTUREMANAGER_H
#define RUEIEGAME_TEXTUREMANAGER_H

#include "EngineBase.h"
#include "SFML/Graphics.hpp"

class TextureManager final {
private:
    static TextureManager *m_Instance;
    TextureManager();
    ~TextureManager();
public:
    static TextureManager* GetInstance();
    static inline std::map<uint64_t, sf::Texture *> m_TextureList = std::map<uint64_t, sf::Texture *>();
    static int LoadTextureFromFile(uint64_t Key, const std::string& Path);
};

#endif //RUEIEGAME_TEXTUREMANAGER_H
