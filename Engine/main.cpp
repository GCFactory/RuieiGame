#include <SFML/Graphics.hpp>

#define DEBUG

#include "Engine.h"
int main()
{
    //получили параметры экрана
    //sf::VideoMode DesktopScreen=sf::VideoMode::getDesktopMode();
    sf::VideoMode DesktopScreen = sf::VideoMode(720, 360, 32);
    auto sfScreenMode = sf::Style::Default;
    sf::RenderWindow MainWindow(sf::VideoMode(DesktopScreen.width,DesktopScreen.height,DesktopScreen.bitsPerPixel),"Game",sfScreenMode);

    MainWindow.setFramerateLimit(60);//установили частоту обновления экрана=60FPS


    Engine engine;

    try {
        engine.Initilaze();
    } catch (std::exception e) {
        std::cout << "[ERROR]" << e.what() << std::endl;
        exit(1);
    }


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