// Game.cpp : Defines the entry point for the application.
//
#define ENGINE_DEBUG

#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Engine.h"
#include "TextureManager.h"

int main()
{
    //sf::VideoMode DesktopScreen=sf::VideoMode::getDesktopMode();//получили параметры экрана
    sf::VideoMode DesktopScreen = sf::VideoMode(720, 360, 32);
    auto sfScreenMode = sf::Style::Default;
    sf::RenderWindow MainWindow(sf::VideoMode(DesktopScreen.width,DesktopScreen.height,DesktopScreen.bitsPerPixel),"Game",sfScreenMode);

    MainWindow.setFramerateLimit(60);//установили частоту обновления экрана=60FPS


    Engine engine;
    TextureManager textureManager;

    auto error = textureManager.LoadTextureFromFile("Resources/Textures/attack_portals.png");
    std::cout << "Texture loaded with exit code: " << error << std::endl;

    GameObject *A =  engine.CreateObject(2);




    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    A->SetPosition(12.34, 113.f);

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