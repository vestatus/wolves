#include "../../inc/graphics/graphics.hpp"
#define its (*it).

BufferedLogger SFMLManager::logger("graphics");

SFMLManager::SFMLManager(std::string title) {
    window.create(sf::VideoMode(width, height), title);
    window.setFramerateLimit(framerate);
    window.clear();
    
    logger.log("SFMLManager created", "SUCC");
}

bool SFMLManager::windowIsOpen() {
    return window.isOpen();
}

bool SFMLManager::checkCloseEvent() {
    logger.log("checking for a close event", "INFO");
    
    queue<sf::Event> e = closeEventRecieved();
    if (! e.empty()) {
        logger.log("window close requested by user, closing window", "INFO");
        window.close();
        logger.log("window closed", "SUCC");
        return true;
    }
    return false;
}

void SFMLManager::render() {
    logger.log("rendering window", "INFO");
    window.display();
    logger.log("window rendered", "SUCC");
}

float sigmoid(float x){
    return 1/(1 + pow(2.71828, x));
}

void SFMLManager::RGBA(sf::Uint8* pixels, int x, int y, int r, int g, int b, int a=255) {
    if ((x < 0) || (y < 0) || (x >= width) || (y >= height)) return;

    int pos = (y * width + x) * 4;

    pixels[pos] = r;
    pixels[pos + 1] = g;
    pixels[pos + 2] = b;
    pixels[pos + 3] = a;
}

void SFMLManager::drawAnimal(sf::Uint8* pixels, int x, int y, Animal* animal) {
    const int maxR = 5; // px
    const int R = maxR * sqrt(animal -> getHunger() * 1.0 / Animal::maxHunger);

    for (int dx=-maxR; dx<maxR+1; dx++) {
        for (int dy=-maxR; dy<maxR+1; dy++) {
            if ((x + dx >= 0) && (y + dy >= 0) && (x + dx < width) && (y + dy < height) && (hypot(dx, dy) < maxR)) {
                if (hypot(dx, dy) <= R) RGBA(pixels, x + dx, y + dy, 0, 0, 255);
                else if (animal -> isHare()) RGBA(pixels, x + dx, y + dy, 0, 255, 0);
                else RGBA(pixels, x + dx, y + dy, 255, 0, 0);
            }
        }
    }
}


void SFMLManager::drawWorld(World &world) {
    logger.log("drawing world", "INFO");
    sf::Texture worldImage;

    bool winterFilter = world.isWinter();

    worldImage.create(width, height);

    ArrayKeeper<sf::Uint8> pxArray(width * height * 4); // encapsulates the array and automatically deletes 
                                                        // at the end of function
    sf::Uint8* pixels = pxArray.getArray();

    

    bool isLand;
    int grass, ht, X, Y;
    int max_ht = 0;

    for(int x=0;x<world.width;x++) 
        for (int y=0;y<world.height;y++) 
            if (max_ht < abs(world.h_map[x][y] - World::SEA_LEVEL)) 
                max_ht = abs(world.h_map[x][y] - World::SEA_LEVEL);

    // draw grass, seas etc.
    for(int x=0;x<width;x++) for (int y=0;y<height;y++) {
        X = x * world.width / width;
        Y = y * world.height / height;

        // scaling to fit infinity into [-256; 255]
        //ht = int(atan((world.h_map[X][Y] - World::SEA_LEVEL) / (SMOOTH_LANDSCAPE ? 100.0 : 100)) * 255 / 1.57); 
        ht = (world.h_map[X][Y] - World::SEA_LEVEL) * 255 / max_ht;

        grass = world.getGrassAt(X, Y);
        isLand = world.isLandAt(X, Y);

         if (isLand) {

            int gr = round(grass * 1.0 / world.GRASS_MAX);
            
            if ((ht < 10) && (ht >= 0)) {
               RGBA(pixels, x, y, 200 + (winterFilter ? 25 : 0), 200+ (winterFilter ? 25 : 0), 100+ (winterFilter ? 25 : 0));
            } else {
                if (winterFilter) RGBA(pixels, x, y, 255, 255, 255);
                else RGBA(pixels, x, y, (255 - ht) *3/4, 255 * 3 /4, ht / 2, grass);
            }
            
        } else {
            if (winterFilter) RGBA(pixels, x, y, (3*255+ht)/4, (3*255+ht)/4, 255 + ht / 2); // ht < 0
            else RGBA(pixels, x, y, (255+ht)/2, (255+ht)/2, 255 + ht / 2); // ht < 0
        }

    }

    int x, y;
    int cnt = 0;


    // draw animals
    for (auto it=Animal::begin(); it != Animal::end(); it++) {
        // cnt++;

        X = (*it)->getX();
        Y = (*it)->getY();

        x = X * width / world.width;
        y =  Y * height / world.height;

        // const int r = 4;

        // int hung = (*it)->getHunger() * 255 / (*it)->maxHunger;

        // for ( int i = -r; i < r + 1; i++ ) 
        //     for ( int j = -r; j < r + 1; j++ ) {
        //         if ( (i * i + j * j) <= r * r) {
        //             RGBA(pixels, x + i, y + j, hung, 255 - hung, 0);
        //         }
        //         if (( (i * i + j * j) <= r * r / 4) && ((*it)->getType() == AnimalType::WOLF)) {
        //             RGBA(pixels, x + i, y + j, 255, 0 , 0);
        //         }
        //     }

        drawAnimal(pixels, x, y, *it);

    }

    for(auto it=Button::begin(); it != Button::end(); it++) {
        drawButtonBackground(*it, pixels);
    }

    worldImage.update(pixels);

    sf::Sprite sprite;
    sprite.setTexture(worldImage);

    window.clear();
    window.draw(sprite);

    for(auto it=Button::begin(); it != Button::end(); it++) {
        drawButtonText(*it);
    }
    

    logger.log("world drawn", "SUCC");
}

void SFMLManager::drawButtonText(Button& button) {
    drawCenteredText(button.text, button.x + button.w / 2, button.y + button.h / 4, 14, sf::Color::Black);
}

void SFMLManager::drawButtonBackground(Button& button, sf::Uint8* pixels) {
    if (button.cl < 250) button.cl += 5;

    for (int i=button.x; i < button.x + button.w; i++) {
        for(int j=button.y; j < button.y + button.h; j++) {
            RGBA(pixels, i, j, button.cl, button.cl, button.cl);
            if ((i - button.x) * (j - button.y - button.h + 1) == 0)
                RGBA(pixels, i, j, 0, 0, 0);
        }
    }
}

void SFMLManager::drawCenteredText(string textString, int x, int y, int size, sf::Color color) {
    sf::Text text;
    sf::Font font;
    font.loadFromFile("res/Inconsolata.otf");

    text.setFont(font);
    text.setString(textString);

    float width = text.getLocalBounds().width;

    text.setPosition(x - width / 4, y);

    text.setCharacterSize(size);
    text.setColor(color);

    window.draw(text);
}

queue<sf::Event> SFMLManager::clickEventRecieved() {
    queue<sf::Event> e;

    if (!clickEvents.empty()) {
        e = clickEvents;
        clickEvents = queue<sf::Event>();
    }

    return e;
}

queue<sf::Event> SFMLManager::closeEventRecieved() {
    queue<sf::Event> e;

    if (!closeEvents.empty()) {
        e = closeEvents;
        closeEvents = queue<sf::Event>();
    }

    return e;
}

bool SFMLManager::checkEvent() {
    sf::Event event;
    bool res = false;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            closeEvents.push(event); 
            res = true;
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            clickEvents.push(event); 
            res = true;

            // cout << event.type.x << " " << event.type.y << "\n"
            sf::Vector2f pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // cout << "click at (" << pos.x << ";" << pos.y << ")\n";

            for(auto it=Button::begin(); it != Button::end(); it++) {
                if ((pos.x > its x) && (pos.x < its x + its w) && (pos.y < its y + its h) && (pos.y > its y)) {
                    its activate();
                }
            }
        }
    }
    return res;
}