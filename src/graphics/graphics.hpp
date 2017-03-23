#pragma once
#include <SFML/Graphics.hpp>
#include "../models/world.hpp"
#include "../tools/containers.hpp"
#include "../logger/logger.hpp"


class SFMLManager{
private:
    sf::RenderWindow window;
    BufferedLogger logger;
public:
    static const int width = 1000;
    static const int height = 500;
    static const int framerate = 60;

    SFMLManager(std::string title);
    bool checkCloseEvent();
    bool windowIsOpen();
    void render();

    void drawWorld(World &world);
};