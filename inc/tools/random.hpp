#pragma once
#include "../tools/containers.hpp"
#include <cmath>
#include <random>
 

class MyRandom
{
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dist;

public:
	MyRandom(){};
    void init( int minVal, int maxVal, int seed );
    int next();
};

class Vector2DRandom {
	MyRandom* random = nullptr;
public:
	pair<float, float> next();
	Vector2DRandom();
};