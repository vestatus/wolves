#pragma once
#include "../models/world.hpp"
#include <vector>

using std::vector;

/*abstract*/ class BaseAI {
protected:
    World* world;
public:
    virtual pair<float, float> decideWhereToGo(vector<vector<float>> animals)=0;
};


class HareAI : public BaseAI {
protected:
    Vector2DRandom vectorRandom;
public:
    pair<float, float> decideWhereToGo(vector<vector<float>> animals);

    HareAI(World* world);
};


class WolfAI : public BaseAI {
public:
    pair<float, float> decideWhereToGo(vector<vector<float>> animals);

    WolfAI(World* world);
};