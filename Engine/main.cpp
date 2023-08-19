#include "Global.h"
#include "Logger.h"
#include "Engine.h"


#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include "Platform/CendricLinux.h"
#endif

#define DEBUG
#define LOG_LEVEL LogLevel::Verbose

int main()
{
#ifndef DEBUG
    #ifdef _WIN32
		HWND hWnd = GetConsoleWindow();
		ShowWindow(hWnd, SW_HIDE);
	#endif
#endif
    g_Logger = new Logger();
#ifdef LOG_LEVEL
    g_Logger->setLogLevel(LOG_LEVEL);
#endif
    g_Engine = new Engine();

    //получили параметры экрана
    //sf::VideoMode DesktopScreen=sf::VideoMode::getDesktopMode();
    sf::VideoMode DesktopScreen = sf::VideoMode(720, 360, 32);
    auto sfScreenMode = sf::Style::Default;
    sf::RenderWindow MainWindow(sf::VideoMode(DesktopScreen.width,DesktopScreen.height,DesktopScreen.bitsPerPixel),"Game",sfScreenMode);

    MainWindow.setFramerateLimit(60);//установили частоту обновления экрана=60FPS

    try {
        g_Engine->Initilaze() ;
    } catch (const std::runtime_error& e) {
        g_Logger->logError("Exception", e.what());
        exit(1);
    }


    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (MainWindow.isOpen())
    {
        sf::Event event{};
        while (MainWindow.pollEvent(event))
        {
            g_Engine->HandleWindowEvent(&MainWindow, event);
        }

        MainWindow.clear();
        MainWindow.draw(shape);
        MainWindow.display();
    }

    delete g_Engine;
    delete g_Logger;

    return 0;
}