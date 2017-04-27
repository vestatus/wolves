#pragma once
#include "../tools/containers.hpp"
#include <cmath>
#include <random>
 

// This class is responsible for generating random numbers in a given range
// It should ideally provide a uniform distribution
// The numbers it returns are not truly random, and the sequence of them has a period
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


// A random generator returning length-1 randomly oriented vectors
// It uses MyRandom to generate a random angle and the returns its cos and sin a vector
class Vector2DRandom {
	MyRandom* random = nullptr;
public:
	pair<float, float> next();
	Vector2DRandom();
	~Vector2DRandom();
};