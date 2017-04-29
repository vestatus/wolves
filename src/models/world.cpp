#include "../../inc/models/world.hpp"
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))


int World::SEA_LEVEL=0;

BufferedLogger worldLogger = BufferedLogger("world");

World::World() {
    const int radius = 200;
    const int c_x=500, c_y=500;

    randomGenerator.init(0, width, 1337);

    grass = std::vector<std::vector<int>>(width, std::vector<int>(height, 0));

    worldLogger.log("world created", "SUCC");    
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
        return h_map[x][y] > SEA_LEVEL;
    }
    else {
        return false;
    }
}

int World::getGrassAt(int x, int y) {
    return grass[x][y];
}

void World::spawnGrass() {
    worldLogger.log("spawning grass", "INFO");
    for (int x=0;x<width;x++) for(int y=0;y<height;y++) {
        grass[x][y] = (isLandAt(x, y) ? (0.5 * GRASS_MAX) : 0);
    }
    worldLogger.log("grass spawned", "SUCC");
}


void World::tick() {
    // grow grass
    for (int x=0;x<width;x++) for(int y=0;y<height;y++) {
        if (grass[x][y] < GRASS_MAX - grass[x][y] * GRASS_GROWTH_RATE) {
            grass[x][y]++;// = int(GRASS_GROWTH_RATE * grass[x][y]);
        }
    }
}


int World::cutGrass(int x, int y, int r, int max, bool forReal) { // not tested, amy be buggy
    const float k = 0.1;
    int d;
    int cutting[2 * r + 1][2 * r + 1];

    int sum = 0;
    for (int i=-r;i<r+1;i++) for(int j=-r;j<r+1;j++) {
        if ((x + i >= 0) && (x + i < width) && (y + j >=0) && (y + j < height)) {
            d = grass[x+i][y+j] * k;
            cutting[r + i][r + j] = d;
            sum += d;
        }
    }

    //std::cout << "sum1 " << sum << " max " << max <<"\n";

    if (sum > max) {
        for (int i=0;i<2*r+1;i++) for(int j=0;j<2*r+1;j++) {
            cutting[i][j] *= max;
            cutting[i][j] /= sum;
        }
    }

    sum = 0;

    for (int i=-r;i<r+1;i++) for(int j=-r;j<r+1;j++) {
        if ((x + i >= 0) && (x + i < width) && (y + j >=0) && (y + j < height)) {
            d = cutting[r + i][r + j];
            if (forReal) grass[x+i][y+j] -= d;
            sum += d;
        }
    }

    //std::cout << "sum2 " << sum << "\n";

    return sum;
}