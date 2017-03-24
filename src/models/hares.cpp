#include "../../inc/models/hares.hpp"
#include "iostream"

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

void Hare::takeTurns() {
	for(list<Hare*>::iterator it=hares.begin(); it != hares.end(); it++) {
		(*it)->takeTurn();
	}
}

void Hare::takeTurn() {

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