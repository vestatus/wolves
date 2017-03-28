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

float Hare::getSpeed(World* world) {
	float res = 1.0 - hunger / 255.0;
	if (! world->isLandAt(round(x), round(y))) {
		res /= 5;
	}
	return res;
}

void Hare::takeTurns(World* world) {
	for(list<Hare*>::iterator it=hares.begin(); it != hares.end(); it++) {
		(*it)->takeTurn(world);
	}

	checkDead();
}

pair<float, float> Hare::decideWhereToGo(World* world) {
	if (turnsMoves--) return direction;
	else if (world->cutGrass(x, y, 5, hunger, false) > 10) {
		return pair<float, float>(0.0, 0.0);
	} else {
		direction = vectorRandom.next();
		turnsMoves = 20;
		return direction;
	}
}

void Hare::die(Hare* hare) { // may cause nullpointerexception in the future...
	dead.push_back(hare);
}

list<Hare*> Hare::dead;

void Hare::checkDead() {
	for(auto it = dead.begin(); it != dead.end(); it ++) {
		hares.remove(*it);
		std::cout << "a hare dies\n";
		delete *it;
	}
	dead.clear();
}

void Hare::takeTurn(World* world) {
	hunger += hungerRate;

	if (hunger > 0)
		hunger = max(0, hunger - world->cutGrass(x, y, 5, hunger));

	//std::cout << hunger << "\n";

	auto vec = decideWhereToGo(world);

	//std::cout << (int)vec.a << " " << (int)vec.b << "\n";

	x += vec.a * getSpeed(world);
	y += vec.b * getSpeed(world);

	if (hunger > maxHunger) Hare::die(this);

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

float Hare::getX() {
	return x;
}

float Hare::getY() {
	return y;
}