#pragma once
#include "../models/world.hpp"
#include "../tools/containers.hpp"
#include "../tools/random.hpp"

using std::cout;
using std::list;

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

enum AnimalType {
    HARE,
    WOLF
};

class Animal {
private:
    static list<Animal*> animals;

    World* world;
    float x, y;
	AnimalType type;
    int hunger=0;
    bool alive=true;
    int getFieldOfView();
public:
	static const int maxHunger = 1000;
	static const int hungerRate = 10; // how many hunger points the hare gains per turn

    Animal(World* world, pair<int, int> coords, AnimalType type);
    int getType();
    float getX();
    float getY();
    int getHunger();
    Vector2DRandom vectorRandom;
    ~Animal();

    float getSpeed();
    bool isAlive();
    void die();
    void eat();
	void takeTurn();
    pair<float, float> decideWhereToGo();
    static void takeTurns();
    static void spawnAnimals(World* world);
    static void removeDead();
    static list<Animal*>::iterator begin();
    static list<Animal*>::iterator end();
};