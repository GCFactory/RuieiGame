// Game.cpp : Defines the entry point for the application.
//
#define ENGINE_DEBUG 1

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Engine.h"
#include "TextureManager.h"
#include "TextureList.h"

int main()
{
    //sf::VideoMode DesktopScreen=sf::VideoMode::getDesktopMode();//получили параметры экрана
    sf::VideoMode DesktopScreen = sf::VideoMode(720, 360, 32);
    auto sfScreenMode = sf::Style::Default;
    sf::RenderWindow MainWindow(sf::VideoMode(DesktopScreen.width,DesktopScreen.height,DesktopScreen.bitsPerPixel),"Game",sfScreenMode);

    MainWindow.setFramerateLimit(60);//установили частоту обновления экрана=60FPS


    Engine engine;

    uint64_t textureId = 1;
//    auto error = TextureManager::LoadTextureFromFile(textureId, "Resources/Textures/attack_portals.png");
    auto error = TextureManager::LoadTextureFromFile(TEXTURE_ATTACK_PORTAL);
    std::cout << "Texture loaded with exit code: " << error << std::endl;

    engine.CreateObject(1);


    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (MainWindow.isOpen())
    {
        sf::Event event;
        while (MainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                MainWindow.close();
        }

        MainWindow.clear();
        MainWindow.draw(shape);
        MainWindow.display();
    }

    return 0;
}