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

        ht = int(atan((world.h_map[X][Y] - World::SEA_LEVEL) / (SMOOTH_LANDSCAPE ? 100.0 : 100)) * 255 / 1.57); // scaling to fit infinity into [-256; 255]

        grass = world.getGrassAt(X, Y);
        isLand = world.isLandAt(X, Y);

         if (isLand) {
            HSV_to_RGB::hsv cl_hsv;
            cl_hsv.h = 100;
            cl_hsv.s = 1 - (ht / 512.0);
            cl_hsv.v = grass * 1.0 / world.GRASS_MAX;

            HSV_to_RGB::rgb cl_rgb = HSV_to_RGB::hsv2rgb(cl_hsv);
            RGB(pixels, x, y, cl_rgb.r * 255, cl_rgb.g * 255, cl_rgb.b * 255);

            //RGB(pixels, x, y, 0, (DRAW_HEIGHT ? (ht / 2) : 0) + grass / 2, 0);
         } else {
            RGB(pixels, x, y, 0, 0, 255 + ht); // ht < 0
         }
    }

    int x, y;
    int cnt = 0;

    for (auto it=Animal::begin(); it != Animal::end(); it++) {
        cnt++;

        X = (*it)->getX();
        Y = (*it)->getY();

        x = X * width / world.width;
        y =  Y * height / world.height;

        const int r = 4;

        int hung = (*it)->getHunger() * 255 / (*it)->maxHunger;

        for ( int i = -r; i < r + 1; i++ ) 
            for ( int j = -r; j < r + 1; j++ ) {
                if ( (i * i + j * j) <= r * r) {
                    RGB(pixels, x + i, y + j, hung, 255 - hung, 0);
                }
                if (( (i * i + j * j) <= r * r / 4) && ((*it)->getType() == AnimalType::WOLF)) {
                    RGB(pixels, x + i, y + j, 255, 0 , 0);
                }
            }

    }

    //std::cout << "drew " << cnt << " animals\n";
    
    Button button = Button(100, 100, 80, 20, "Click me!");
    drawButtonBackground(button, pixels);

    worldImage.update(pixels);

    sf::Sprite sprite;
    sprite.setTexture(worldImage);

    //window.clear();
    window.draw(sprite);

    drawButtonText(button);
    

    logger.log("world drawn", "SUCC");
}

void SFMLManager::drawButtonText(Button& button) {
    drawCenteredText(button.text, button.x + button.w / 2, button.y, 14, sf::Color::Black);
}

void SFMLManager::drawButtonBackground(Button& button, sf::Uint8* pixels) {
    for (int i=button.x; i < button.x + button.w; i++) {
        for(int j=button.y; j < button.y + button.h; j++) {
            RGB(pixels, i, j, 250, 250, 250);
            if ((i - button.x) * (j - button.y) * (i - button.x - button.w + 1) * (j - button.y - button.h + 1) == 0)
                RGB(pixels, i, j, 0, 0, 0);
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