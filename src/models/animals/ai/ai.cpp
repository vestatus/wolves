pair<float, float> Animal::decideWhereToGo() {
	if (type == AnimalType::HARE) {
		#include "hare_ai.cpp"
	} else if (type == AnimalType::WOLF) {
		#include "wolf_ai.cpp"
	}
}