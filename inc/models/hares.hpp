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
	int hunger;
	float x, y;
	void takeTurn(World* world);
	Hare();
    Vector2DRandom vectorRandom;
    pair<float, float> direction;
    int turnsMoves=0;
public:
	static const int maxHunger = 1000;
	static const int hungerRate = 10;
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
	int getHunger();

	Hare(int x, int y);
};