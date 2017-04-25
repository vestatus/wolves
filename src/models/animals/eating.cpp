#define square(x) ((x) * (x))

void Animal::eat() {
	if (type == AnimalType::HARE) {
	    if (world->isLandAt(x, y)) {

	        if (hunger > 0) {
	            hunger = max(0, hunger - world->cutGrass(x, y, 2, hunger));
	        }
	    }
	} else if (type == AnimalType::WOLF) {
		for(auto it=begin(); it != end(); it++) {
			if (square((*it)->getX() - x) + square((*it)->getY() - y) <= 25) {
				if ((*it)->getType() == AnimalType::HARE) {
					(*it)->die();
					decreaseHunger(hareHungerValue);
					std::cout << "a wolf has eaten a hare\n";
				}
			}
		}
	}
}