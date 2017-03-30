#pragma once
#include <list>
#include "../models/world.hpp"
#include "../tools/random.hpp"
#include "../tools/containers.hpp"

using std::list;

class Hare {
protected:
	static list<Hare*> hares;
	static list<Hare*> dead; // pointers to hares who died this turn
	int hunger;
	float x, y; // position of the hare on the map (not on the screen)
	void takeTurn(World* world); // decide where to go, become hungry, die etc.
	Hare();
    Vector2DRandom vectorRandom; // generator capable of producing random length 1 vectors
    pair<float, float> direction; // length 1 speed vector
    int turnsMoves=0; // how many turns the hare will move in that direction
public:
	static const int maxHunger = 1000;
	static const int hungerRate = 10; // how many hunger points the hare gains per turn
	static void takeTurns(World* world); // call takeTurn on every hare
	static list<Hare*>::iterator startOfHares(); // returns iterator pointing to the start of Hare::hares
	static list<Hare*>::iterator endOfHares(); // returns iterator pointing to the end of Hare::hares
	static void spawnHare(int x, int y);
	static void spawnHares(World* world); // spawn the initial amount of hares
	static void die(Hare* hare); // maybe should be redone as non-static Hare::die()
	static void checkDead(); // delete the dead hares from Hare::hares and clear Hare::dead
	pair<float, float> decideWhereToGo(World* world); // return a length 1 direction vector
	float getX();
	float getY();
	float getSpeed(World* world);
	int getHunger();

	Hare(int x, int y);
};