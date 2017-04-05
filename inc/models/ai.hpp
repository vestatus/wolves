#pragma once
#include "../models/world.hpp"

/*abstract*/ class BaseAI {
protected:
    World* world;
public:
    virtual pair<float, float> decideWhereToGo()=0;
};


class HareAI : public BaseAI {
protected:
    Vector2DRandom vectorRandom;
public:
    pair<float, float> decideWhereToGo();

    HareAI(World* world);
};


class WolfAI : public BaseAI {
public:
    pair<float, float> decideWhereToGo();

    WolfAI(World* world);
};