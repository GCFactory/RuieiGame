//
// Created by Alex on 8/14/2023.
//

#include "Global.h"
#include "Logger.h"
#include "Engine.h"
#include "TextureList.h"
#include "TextureManager.h"

Engine* g_Engine;

Engine::Engine() {
    GameObjectList.reserve(256);
}

void Engine::Initilaze() {
    int error = 0;
    for (uint32_t i = 1; i <= TextureList.size(); i++) {
        g_Logger->log(LogLevel::Verbose, "Engine", std::format("Try to load texture {}", TextureList[i]));
        error = TextureManager::LoadTextureFromFile(i, TextureList[i]);
        if (error != 0) {
            switch (error) {
                case ERROR_TEXTURE_ALREADY_DECLARED:
                    g_Logger->log(LogLevel::Warning, "Engine", std::format("Texture already loaded \"{}\"", TextureList[i]));
                    break;
                case ERROR_TEXTURE_NOT_LOADED:
                    g_Logger->log(LogLevel::Error, "Engine", std::format("Texture not loaded \"{}\"", TextureList[i]));
                    throw std::runtime_error("EngineException");
                default:
                    g_Logger->log(LogLevel::Error, "Engine", std::format("Failed to load texture \"{}\"", TextureList[i]));
                    throw std::runtime_error("EngineException");
            }
        }
    }
    g_Logger->log(LogLevel::Verbose, "Engine", "Textures loaded");
}

void Engine::HandleWindowEvent(RenderWindow *window, Event event) {
    if (event.type == sf::Event::Closed) {
        window->close();
    }
}
