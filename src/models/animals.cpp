#include "../../inc/models/animals.hpp"

list<Animal*> Animal::animals;

Animal::Animal(World* world, BaseAI* ai, pair<int, int> coords, AnimalType type) {
    this->world = world;
    this->ai = ai;
    this->type = type;
    x = coords.a;
    y = coords.b;
}

float Animal::getX() {return x;}
float Animal::getY() {return y;}
int Animal::getHunger() {return hunger;}
Animal::~Animal() {}

float Animal::getSpeed() {
    float res = 1 - (float)hunger / maxHunger;
    if (! world->isLandAt(round(x), round(y))) {
        res /= 5;
    }
    return res;
}

vector<float> Animal::encode() {
    // Формат вектора:
    // 0 и 1 элементы -- координаты x и y
    // 2 элемент -- тип животного (1 у волка и 0 у зайца)

    vector<float> res;
    res.push_back(getX());
    res.push_back(getY());
    res.push_back((type == AnimalType::WOLF) ? 1 : 0);

    return res;
}

void Animal::die() {
    cout << animals.size() << " little niggers left\n";
    alive = false;
}

bool Animal::isAlive() {
    return alive;
}

void Animal::eat() {
    if (world->isLandAt(x, y)) {

        if (hunger > 0) {
            hunger = max(0, hunger - world->cutGrass(x, y, 2, hunger));
        }
    }
}

void Animal::takeTurn() { // decide where to go, become hungry, die etc.
    hunger += hungerRate;
    if (hunger > maxHunger) die();


    eat();

    //std::cout << hunger << "\n";

    auto vec = ai->decideWhereToGo(vector<vector<float>>{this->encode()});

    //std::cout << (int)vec.a << " " << (int)vec.b << "\n";

    x += vec.a * getSpeed();
    y += vec.b * getSpeed();
}

void Animal::takeTurns() {
    for(auto it = animals.begin(); it != animals.end(); it++) {
        if ((*it)->isAlive()) {
            (*it)->takeTurn();
        }
    }

    removeDead();
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
    const int N = 50;

    animals = list<Animal*>();

    HareAI* hareAI = new HareAI(world);
    WolfAI* wolfAI = new WolfAI(world);  // memleak

    pair<int, int> coords;

    for (int i=0; i < N; i++) {
        coords = world->getRandomLand();
        animals.push_back(new Animal(world, hareAI, coords, AnimalType::HARE));

        coords = world->getRandomLand();
        animals.push_back(new Animal(world, wolfAI, coords, AnimalType::WOLF));
    }
}


list<Animal*>::iterator Animal::begin() {
    return animals.begin();
}

list<Animal*>::iterator Animal::end() {
    return animals.end();
}