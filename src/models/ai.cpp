#include "../../inc/models/ai.hpp"


HareAI::HareAI(World* world) {
        this->world = world;
}

WolfAI::WolfAI(World* world) {
        this->world = world;
}

pair<float, float> WolfAI::decideWhereToGo() {
     //cout << "wolf thinks...\n"; 
     return pair<float, float>(0, 0);
}

pair<float, float> HareAI::decideWhereToGo() {
     //cout << "hare thinks...\n"; 
     return vectorRandom.next();
}