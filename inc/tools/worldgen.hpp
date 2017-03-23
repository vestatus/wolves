#pragma once
#include <cstdlib>
#include "../logger/logger.hpp"
#include "../tools/random.hpp"

class WorldGenerator {
protected:
	const float R = 0.01; // roughness
    int seed;
    int size; // 2 ** n + 1
    MyRandom random;

    void diamond(int** hmap, int w);
    void square(int** hmap, int w);
    void smoothe(int** hmap);

public:
    WorldGenerator(int size, int seed);
    ~WorldGenerator();
    void generate(int** hmap);

};