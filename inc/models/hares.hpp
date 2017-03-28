#pragma once
#include <list>
#include "../models/world.hpp"
#include "../tools/random.hpp"
#include "../tools/containers.hpp"

using std::list;

class Hare {
protected:
	static list<Hare*> hares;
	static list<Hare*> dead;
	static const int maxHunger = 1000;
	static const int hungerRate = 100;
	int hunger;
	float x, y;
	void takeTurn(World* world);
	Hare();
    Vector2DRandom vectorRandom;
    pair<float, float> direction;
    int turnsMoves=0;
public:
	static void takeTurns(World* world);
	static list<Hare*>::iterator startOfHares();
	static list<Hare*>::iterator endOfHares();
	static void spawnHare(int x, int y);
	static void spawnHares(World* world);
	static void die(Hare* hare);
	static void checkDead();
	pair<float, float> decideWhereToGo(World* world);
	float getX();
	float getY();
	float getSpeed(World* world);

	Hare(int x, int y);
};