#pragma once
#include "../world.hpp"
#include "../../tools/containers.hpp"
#include "../../tools/random.hpp"

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
    static list<Animal*> babies;

    World* world;
    float x, y;
    float vx=0, vy=0;
	AnimalType type;
    int hunger=0;
    bool alive=true;
    int getFieldOfView();
    Vector2DRandom vectorRandom;
    void decreaseHunger(int delta);
    void increaseHunger(int delta);
    double age = 0;
public:
	static const int maxHunger = 3000;
	static const int hungerRate = 2; // how many hunger points the animal gains per turn
    static const int hareHungerValue = maxHunger / 10;
    static const int BREEDING_RADIUS = 10;
    static const int MAX_BREEDING_HUNGER = 200;
    static const int BREEDING_DELTA_HUNGER = 800;
    static const int MIN_BREEDING_AGE = 300;
    static const int MAX_AGE = 10000;
    static const int N_hares = 50;
    static const int N_wolves = 6;

    Animal(World* world, pair<int, int> coords, AnimalType type);
    int getType();
    float getX();
    float getY();
    pair<float, float> getCoords();
    pair<float, float> getSpeedVector();
    int getHunger();
    ~Animal();

    float getSpeed();
    bool isAlive();
    void die();
    void eat();
	void takeTurn();
    bool isHare();
    bool isWolf();
    pair<float, float> decideWhereToGo();
    static void takeTurns();
    static void spawnAnimals(World* world);
    static void removeDead();
    static list<Animal*>::iterator begin();
    static list<Animal*>::iterator end();
};