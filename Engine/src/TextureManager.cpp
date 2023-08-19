//
// Created by Alex on 8/13/2023.
//
#include "SFML/Graphics/Texture.hpp"

#include "Global.h"
#include "Enums/ErrorID.h"
#include "Logger.h"
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
            TextureManager::TextureList.insert_or_assign(Key, t);
            g_Logger->log(LogLevel::Debug, "TextureManager", std::format("New texture loaded with id={}", Key));
            return 0;
        }
    }
}