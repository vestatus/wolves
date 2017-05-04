#pragma once
#include <cmath>
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include "../logger/logger.hpp"
#include "../tools/worldgen.hpp"
#include "../tools/containers.hpp"
#include "../tools/random.hpp"

class World{
public:
    static const int width = 513; // the world's real size, less or equal 
                                                // to the size of what DiamondSquare generates
    static const int height = 513;
    static const int GRASS_MAX = 255; // maximum amount of grass per tile
    static int SEA_LEVEL; // approximately zero
    static constexpr float GRASS_GROWTH_RATE = 0.2; // >= 0, needed for linear grass growth
    static constexpr float GRASS_CUTTING_COEF = 1;
    static constexpr float GRASS_CUTTING_EFFICIENCY = 0.1;
private:
    std::vector<std::vector<float>> grass; // 2D-vector of grass
    MyRandom randomGenerator; // generates random ints, see tools/MyRandom.hpp for more info

public:
    int h_map[width][height]; // how elevated the tile at (x, y) is. In range(-inf, inf)

    pair<int, int> getRandomLand(); // get a pair of random coordinates. 
                                        // At these coordinates there should be land, and not sea
    void spawnGrass();
    int getGrassAt(int x, int y); // get the amount of grass at (x, y). In range(0, GRASS_MAX)

    // if forReal == true, cut no more than max grass in the circle(x, y, r). Return the amount of grass cut.
    // Otherwise just return the amount of grass that would be cut if forReal were true
    int cutGrass(int x, int y, int r, int max, bool forReal=true);

    bool isLandAt(int x, int y); // is it land or sea at (x, y)?
    void readIslands(); // deprecated
    void generate(); // generate this world
    void tick(); // update the world: grow grass etc.

    World();
};