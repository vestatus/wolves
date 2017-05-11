#include "../../../inc/models/animals/animals.hpp"
#include "ai/ai.cpp"
#include "eating.cpp"
#define square(x) ((x) * (x))

list<Animal*> Animal::animals;
list<Animal*> Animal::babies;

Animal::Animal(World* world, pair<int, int> coords, AnimalType type) {
    this->world = world;
    this->type = type;
    x = coords.a;
    y = coords.b;
}

float Animal::getX() {return x;}
float Animal::getY() {return y;}
int Animal::getHunger() {return hunger;}
Animal::~Animal() {}

float Animal::getSpeed() {
    float res = 0.8 + (float)hunger / maxHunger / 5;
    if (! world->isLandAt(round(x), round(y))) {
        res /= 4;
    }
    if (type == AnimalType::WOLF) res *= WOLF_SPEED_MULTIPLIER;
    return res;
}

void Animal::die() {
    // cout << animals.size() << " little niggers left\n";
    alive = false;
}

bool Animal::isAlive() {
    return alive;
}



void Animal::takeTurn() { // decide where to go, become hungry, die etc.
    age++;
    increaseHunger(hungerRate);

    eat();

    //std::cout << hunger << "\n";

    auto vec = (decideWhereToGo().scale(1) + getSpeedVector().scale(0.1)).scale(1);

    //std::cout << (int)vec.a << " " << (int)vec.b << "\n";

    vx = vec.a * getSpeed();
    vy = vec.b * getSpeed();

    x += vx;
    y += vy;

    for (auto it=begin();it != end(); it++) {
        if (((*it)->type == type) && 
                (*it != this) &&
                alive && (*it)->alive && 
                ((age >= MIN_BREEDING_AGE) && ((*it)->age >= MIN_BREEDING_AGE)) &&
                (dist(getCoords(), (*it)->getCoords()) < BREEDING_RADIUS) &&
                ((hunger < MAX_BREEDING_HUNGER) && ((*it)->hunger < MAX_BREEDING_HUNGER))
                ) {
            hunger += BREEDING_DELTA_HUNGER;
            (*it)->hunger += BREEDING_DELTA_HUNGER;
            pair<int, int> babyCoords = ((getCoords() + (*it)->getCoords()) / 2).as<int, int>();
            babies.push_back(new Animal(world, babyCoords, type));
            // cout << "A baby " << ((type == AnimalType::WOLF) ? "WOLF" : "HARE") << " has been born at " << babyCoords.a << ";" << babyCoords.b << "\n";
        }
    }

    if ((age > MAX_AGE) && alive ) die();
}

pair<float, float> Animal::getSpeedVector() {
    return pair<float, float>(vx, vy);
}

int Animal::getFieldOfView() {
    return 50;
}

void Animal::takeTurns() {
    for(auto it = animals.begin(); it != animals.end(); it++) {
        if ((*it)->isAlive()) {
            (*it)->takeTurn();
        }
    }

    removeDead();

    for (auto it=babies.begin(); it != babies.end(); it++) {
        animals.push_back(*it);
    }

    babies.clear();
}

void Animal::removeDead() {
    list<Animal*> upd;

    for(auto it = animals.begin(); it != animals.end(); it++) {
        if ((*it)->isAlive()) {
            upd.push_back(*it);
        } else {
            delete *it;
        }
    }

    animals = upd;
}

int Animal::getType() {
    return type;
}

void Animal::spawnAnimals(World* world) {

    for(auto it=animals.begin(); it != animals.end(); it++) {
        delete *it;
    }

    animals = list<Animal*>();

    pair<int, int> coords;

    for (int i=0; i < N_hares; i++) {
        coords = world->getRandomLand();
        animals.push_back(new Animal(world, coords, AnimalType::HARE));
    }

    for (int i=0; i < N_wolves; i++) {
        coords = world->getRandomLand();
        animals.push_back(new Animal(world, coords, AnimalType::WOLF));
    }
}


list<Animal*>::iterator Animal::begin() {
    return animals.begin();
}

list<Animal*>::iterator Animal::end() {
    return animals.end();
}

void Animal::decreaseHunger(int delta) {
    hunger = ((hunger - delta) < 0) ? : (hunger - delta);
}

void Animal::increaseHunger(int delta) {
    hunger += delta;
    if (hunger > maxHunger) die();
}

bool Animal::isHare() {
    return type == AnimalType::HARE;
}

bool Animal::isWolf() {
    return type == AnimalType::WOLF;
}

pair<float, float> Animal::getCoords() {
    return pair<float, float>(x, y);
}