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
    static const int width = 513;
    static const int height = 513;
    static const int GRASS_MAX = 255;
    static constexpr double GRASS_GROWTH_RATE = 1.01;
private:
    bool land[width][height];
    std::vector<std::vector<int>> grass;
    BufferedLogger logger;
    MyRandom randomGenerator;

public:
    int h_map[width][height];

    pair<int, int> getRandomLand();
    void spawnGrass();
    int getGrassAt(int x, int y);
    int cutGrass(int x, int y, int r, int max);
    bool isLandAt(int x, int y);
    void readIslands();
    void generate();
    void tick();

    World();
};