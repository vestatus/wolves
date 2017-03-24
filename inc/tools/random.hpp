#pragma once
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