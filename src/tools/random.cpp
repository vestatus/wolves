#include "../../inc/tools/random.hpp"

void MyRandom::init( int minVal, int maxVal, int seed ) {
    dist = std::uniform_int_distribution<>(minVal, maxVal);
    gen = std::mt19937(rd());
}


int MyRandom::next() {
    return dist(gen);
}