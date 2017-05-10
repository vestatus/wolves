#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <queue>
#include "../models/world.hpp"
#include "../tools/containers.hpp"
#include "../tools/algorythms.hpp"
#include "../logger/logger.hpp"
#include "../models/animals/animals.hpp"
#include "../graphics/button.hpp"

using std::queue;

class SFMLManager{ // This class encapsulates SFML
private:
    sf::RenderWindow window;
    static BufferedLogger logger;
    queue<sf::Event> closeEvents;
    queue<sf::Event> clickEvents;
    void drawButtonBackground(Button& button, sf::Uint8* pixels);
    void drawButtonText(Button& button);
    static void RGBA(sf::Uint8* pixels, int x, int y, int r, int g, int b, int a); // draw a dot into SFML buffer
    void drawAnimal(sf::Uint8* pixels, int x, int y, Animal* animal);
public:
    static const int width = 700;
    static const int height = 700;
    static const int framerate = 60;
    static const bool DRAW_HEIGHT = false; // whether to show terrain height on the map or not
    static const bool SMOOTH_LANDSCAPE = false;

    SFMLManager(std::string title);
    bool checkEvent();
    bool checkCloseEvent(); // close the window if the user says so
    queue<sf::Event> clickEventRecieved();
    queue<sf::Event> closeEventRecieved();
    bool windowIsOpen();
    void render(); // draw the SFML buffer to the screen
    void drawCenteredText(string textString, int x, int y, int size, sf::Color color);

    void drawWorld(World &world); // draw the world into SFML buffer
};