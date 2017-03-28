#include "../../inc/tools/random.hpp"

void MyRandom::init( int minVal, int maxVal, int seed ) {
    dist = std::uniform_int_distribution<>(minVal, maxVal);
    gen = std::mt19937(rd());
}


int MyRandom::next() {
    return dist(gen);
}

Vector2DRandom::Vector2DRandom() {
	if (random == nullptr) {
		random = new MyRandom();
		random->init(0, 36000, 32469);
	}
}

pair<float, float> Vector2DRandom::next() {
	float rnd = random->next() * 0.01;
	return pair<float, float>(cos(rnd), sin(rnd));
}