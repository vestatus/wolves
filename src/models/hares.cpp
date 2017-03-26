#include "../../inc/models/hares.hpp"
#include "iostream"

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

list<Hare*> Hare::hares;

Hare::Hare(int x, int y) {
	this->x = x;
	this->y = y;
	hunger = 0;
}

void Hare::spawnHare(int x, int y) {
	Hare* ptr = new Hare(x, y);
	hares.push_back(ptr);
}

int Hare::getSpeed() {
	return 255 - hunger;
}

void Hare::takeTurns(World* world) {
	for(list<Hare*>::iterator it=hares.begin(); it != hares.end(); it++) {
		(*it)->takeTurn(world);
	}
}

void Hare::takeTurn(World* world) {
	hunger = max(0, hunger - world->cutGrass(x, y, 5));
	x++;
}

void Hare::spawnHares(World* world) {
	pair<int, int> coords;
    for (int i=0; i<100;i++) {
        coords = world->getRandomLand();
        Hare::spawnHare(coords.a, coords.b);
    }
}


list<Hare*>::iterator Hare::startOfHares() {
	return hares.begin();
}

list<Hare*>::iterator Hare::endOfHares() {
	return hares.end();
}

int Hare::getX() {
	return x;
}

int Hare::getY() {
	return y;
}