#include "../../inc/models/world.hpp"
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

World::World() {
    const int radius = 200;
    const int c_x=500, c_y=500;

    randomGenerator.init(0, width, 1337);

    grass = std::vector<std::vector<int>>(width, std::vector<int>(height, 0));

    for(int X=0; X < width; X++)
        for(int Y=0; Y < height; Y++)
        {
            if (pow(c_x - X, 2) + pow(c_y - Y, 2) <= pow(radius, 2))
                land[X][Y] = true;
            else
                land[X][Y] = false;
        }

    logger = BufferedLogger("world");
    logger.log("world created", "SUCC");    
}

void World::generate() {
    int size = max(width, height);
    WorldGenerator generator(width, 1337);
    Array2DKeeper<int> hmap(width, height);

    generator.generate(hmap.getArray2D());
    int** array2d = hmap.getArray2D();

    int thd = 0;
    for(int x=0;x<width;x++)
        for(int y=0;y<height;y++) {
            land[x][y] = array2d[x][y] > thd;
            h_map[x][y] = array2d[x][y];
        }

}

pair<int, int> World::getRandomLand() {
    int x, y;

    do {
        x = randomGenerator.next();
        y = randomGenerator.next();
    } while(!isLandAt(x, y));

    return pair<int, int>(x, y);
}

bool World::isLandAt(int x, int y) {
    if ((x >= 0) && (x < width) && (y >= 0) && (y < height)) {
        return land[x][y];
    }
    else {
        return false;
    }
}

int World::getGrassAt(int x, int y) {
    return grass[x][y];
}

void World::readIslands() {
    std::fstream stream("res/islands.txt", std::ios_base::in);

    int x, y, r;


    while(stream.good()) {
        stream >> x >> y >> r;
        logger.log("loading island with x=" + std::to_string(x) + 
            ", y=" + std::to_string(y) + " r=" + std::to_string(r), "INFO");

        for(int X=max(x-r, 0); X < min(x+r+1, width); X++)
            for(int Y=max(y-r, 0); Y < min(y+r+1, height); Y++)
            {
                if (pow(x - X, 2) + pow(y - Y, 2) <= pow(r, 2)) {
                    land[X][Y] = true;
                }
            }
    }
    logger.log("islands loaded", "SUCC");
}

void World::spawnGrass() {
    logger.log("spawning grass", "INFO");
    for (int x=0;x<width;x++) for(int y=0;y<height;y++) {
        grass[x][y] = (land[x][y] ? (0.5 * GRASS_MAX) : 0);
    }
    logger.log("grass spawned", "SUCC");
}


void World::tick() {
    for (int x=0;x<width;x++) for(int y=0;y<height;y++) {
        if (grass[x][y] < GRASS_MAX - grass[x][y] * GRASS_GROWTH_RATE) {
            grass[x][y] = int(GRASS_GROWTH_RATE * grass[x][y]);
        }
    }

    Hare::takeTurns();
}

void World::spawnStuff() {
    spawnGrass();
    spawnHares();
    spawnWolves();
}

void World::spawnHares() {
    pair<int, int> coords;
    for (int i=0; i<100;i++) {
        coords = getRandomLand();
        Hare::spawnHare(coords.a, coords.b);
    }
}

void World::spawnWolves() {

}