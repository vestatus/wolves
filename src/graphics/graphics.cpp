#include "graphics.hpp"

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


void SFMLManager::drawWorld(World &world) {
    logger.log("drawing world", "INFO");
    sf::Texture worldImage;

    worldImage.create(width, height);

    ArrayKeeper<sf::Uint8> pxArray(width * height * 4); // encapsulates the array and automatically deletes at the end of function
    sf::Uint8* pixels = pxArray.getArray();

    bool isLand;
    int grass;

    for(int x=0;x<width;x++) for (int y=0;y<height;y++) {
        pixels[(y * width + x) * 4 + 3] = 230; // alpha channel

        isLand = world.isLandAt(x * world.width / width, y * world.height / height);
        grass=0;
        if (isLand) grass = world.getGrassAt(x * world.width / width, y * world.height / height);

        pixels[(y * width + x) * 4 + 1] = isLand ? 128 : 0; // green
        pixels[(y * width + x) * 4] = isLand ? 255 - grass * 255 / world.GRASS_MAX : 0; // red

        if (!isLand) pixels[(y * width + x) * 4 + 2] = 128; // blue
    }
    worldImage.update(pixels);

    worldImage.setSmooth(true);

    sf::Sprite sprite;
    sprite.setTexture(worldImage);

    window.clear();
    window.draw(sprite);

    logger.log("world drawn", "SUCC");
}