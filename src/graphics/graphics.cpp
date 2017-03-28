#include "../../inc/graphics/graphics.hpp"

SFMLManager::SFMLManager(std::string title) {
    window.create(sf::VideoMode(width, height), title);
    window.setFramerateLimit(framerate);
    window.clear();

    logger = BufferedLogger("graphics");
    logger.log("SFMLManager created", "SUCC");
}

bool SFMLManager::windowIsOpen() {
    return window.isOpen();
}

bool SFMLManager::checkCloseEvent() {
    logger.log("checking for a close event", "INFO");
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) {
            logger.log("window close requested by user, closing window", "INFO");
            window.close();
            logger.log("window closed", "SUCC");
            return true;
        }
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

void SFMLManager::RGB(sf::Uint8* pixels, int x, int y, int r, int g, int b) {
    if ((x < 0) || (y < 0) || (x >= width) || (y >= height)) return;

    int pos = (y * width + x) * 4;

    pixels[pos] = r;
    pixels[pos + 1] = g;
    pixels[pos + 2] = b;
    pixels[pos + 3] = 255;
}

void SFMLManager::drawWorld(World &world) {
    logger.log("drawing world", "INFO");
    sf::Texture worldImage;

    worldImage.create(width, height);

    ArrayKeeper<sf::Uint8> pxArray(width * height * 4); // encapsulates the array and automatically deletes at the end of function
    sf::Uint8* pixels = pxArray.getArray();

    bool isLand;
    int grass, ht, X, Y;

    for(int x=0;x<width;x++) for (int y=0;y<height;y++) {
        X = x * world.width / width;
        Y = y * world.height / height;

        ht = int(atan(world.h_map[X][Y] / 100) * 255 / 1.57); // scaling to fit infinity into [-256; 255]

        grass = world.getGrassAt(X, Y);
        isLand = world.isLandAt(X, Y);

         if (isLand) {
            RGB(pixels, x, y, 0, (DRAW_HEIGHT ? (ht / 2) : 0) + grass / 2, 0);
         } else {
            RGB(pixels, x, y, 0, 0, 255 + ht); // ht < 0
         }
    }

    int x, y;

    for (list<Hare*>::iterator it=Hare::startOfHares(); it != Hare::endOfHares(); it++) {
        X = (*it)->getX();
        Y = (*it)->getY();

        x = X * width / world.width;
        y =  Y * height / world.height;

        const int r = 5;

        for ( int i = -r; i < r + 1; i++ ) 
            for ( int j = -r; j < r + 1; j++ ) {
                if ( (i * i + j * j) <= r * 2) {
                    RGB(pixels, x + i, y + j, 127, 127, 127);
                }
            }

    }


    worldImage.update(pixels);

    sf::Sprite sprite;
    sprite.setTexture(worldImage);

    window.clear();
    window.draw(sprite);

    logger.log("world drawn", "SUCC");
}