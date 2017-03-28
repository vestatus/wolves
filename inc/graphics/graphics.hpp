#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "../models/world.hpp"
#include "../tools/containers.hpp"
#include "../logger/logger.hpp"
#include "../models/hares.hpp"


class SFMLManager{
private:
    sf::RenderWindow window;
    BufferedLogger logger;
    static void RGB(sf::Uint8* pixels, int x, int y, int r, int g, int b);
public:
    static const int width = 1000;
    static const int height = 500;
    static const int framerate = 60;
    static const bool DRAW_HEIGHT = false;

    SFMLManager(std::string title);
    bool checkCloseEvent();
    bool windowIsOpen();
    void render();

    void drawWorld(World &world);
};