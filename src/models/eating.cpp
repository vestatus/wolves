void Animal::eat() {
	if (type == AnimalType::HARE) {
	    if (world->isLandAt(x, y)) {

	        if (hunger > 0) {
	            hunger = max(0, hunger - world->cutGrass(x, y, 2, hunger));
	        }
	    }
	} else if (type == AnimalType::WOLF) {
		
	}
}