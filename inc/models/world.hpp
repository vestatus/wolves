#pragma once
#include <cmath>
#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include "../logger/logger.hpp"
#include "../tools/worldgen.hpp"
#include "../tools/containers.hpp"
#include "../models/hares.hpp"
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

    void spawnGrass();
    void spawnHares();
    void spawnWolves();
public:
    int h_map[width][height];

    pair<int, int> getRandomLand();
    int getGrassAt(int x, int y);
    bool isLandAt(int x, int y);
    void readIslands();
    void spawnStuff();
    void generate();
    void tick();

    World();
};