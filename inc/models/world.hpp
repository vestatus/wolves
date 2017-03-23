#pragma once
#include <cmath>
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include "../logger/logger.hpp"
#include "../models/worldgen.hpp"
#include "../tools/containers.hpp"

class World{
public:
    static const int width = 1025;
    static const int height = 1025;
    static const int GRASS_MAX = 1000000;
    static constexpr double GRASS_GROWTH_RATE = 1.01;
private:
    bool land[width][height];
    std::vector<std::vector<int>> grass;
    BufferedLogger logger;
public:
    World();
    bool isLandAt(int x, int y);
    int getGrassAt(int x, int y);
    void readIslands();
    void spawnGrass();
    void generate();
    void tick();
};