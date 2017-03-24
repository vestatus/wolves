#pragma once
#include <list>

using std::list;

class Hare {
protected:
	static list<Hare*> hares;
	int hunger;
	int x, y;
	void takeTurn();
	Hare();
public:
	static void takeTurns();
	static list<Hare*>::iterator startOfHares();
	static list<Hare*>::iterator endOfHares();
	static void spawnHare(int x, int y);
	int getX();
	int getY();
	int getSpeed();

	Hare(int x, int y);
};