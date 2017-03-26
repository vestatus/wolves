#pragma once
#include <list>
#include "../models/world.hpp"
#include "../tools/containers.hpp"

using std::list;

class Hare {
protected:
	static list<Hare*> hares;
	int hunger;
	int x, y;
	void takeTurn(World* world);
	Hare();
public:
	static void takeTurns(World* world);
	static list<Hare*>::iterator startOfHares();
	static list<Hare*>::iterator endOfHares();
	static void spawnHare(int x, int y);
	static void spawnHares(World* world);
	int getX();
	int getY();
	int getSpeed();

	Hare(int x, int y);
};