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


void SFMLManager::drawWorld(World &world) {
    logger.log("drawing world", "INFO");
    sf::Texture worldImage;

    worldImage.create(width, height);

    ArrayKeeper<sf::Uint8> pxArray(width * height * 4); // encapsulates the array and automatically deletes at the end of function
    sf::Uint8* pixels = pxArray.getArray();

    bool isLand;
    int grass, ht, X, Y;

    for(int x=0;x<width;x++) for (int y=0;y<height;y++) {
        pixels[(y * width + x) * 4 + 3] = 230; // alpha channel

        X = x * world.width / width;
        Y = y * world.height / height;

        ht = int(atan(world.h_map[X][Y] / 100) * 255 / 1.57);

        grass = world.getGrassAt(X, Y);
        isLand = world.isLandAt(X, Y);

         if (isLand) {
            pixels[(y * width + x) * 4 + 1] = ht / 2 + grass / 2; // green
            //pixels[(y * width + x) * 4] = 255 - ht / 2 - grass;
            //ixels[(y * width + x) * 4 + 2] = 255 - ht / 2  - grass;
         } else {
            pixels[(y * width + x) * 4 + 2] = 255 + ht;
         }
    }
    worldImage.update(pixels);

    worldImage.setSmooth(true);

    sf::Sprite sprite;
    sprite.setTexture(worldImage);

    window.clear();
    window.draw(sprite);

    logger.log("world drawn", "SUCC");
}