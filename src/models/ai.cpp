#include "../../inc/models/ai.hpp"


HareAI::HareAI(World* world) {
        this->world = world;
}

WolfAI::WolfAI(World* world) {
        this->world = world;
}

pair<float, float> WolfAI::decideWhereToGo(vector<vector<float>> animals) {
		// Формат такой:
		// animals -- вектор животных, которые закодированы методом Animal::encode()
		// нулевой элемент этого вектора -- то животное, ии которого сейчас думает, куда ему идти
		// прочую информацию о мире можно получить из переменной world (это указатель на мир)
	for(auto it=animals.begin(); it != animals.end(); it++) {
		std::cout << (*it)[1] << "\n";
	}
    return pair<float, float>(0, 0);
}

pair<float, float> HareAI::decideWhereToGo(vector<vector<float>> animals) {

     return vectorRandom.next();
}