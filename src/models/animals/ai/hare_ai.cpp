const int radius = 50;
pair<float, float> sum(0, 0);

for(auto it=begin(); it != end(); it++) {
	if ((*it)->isWolf()) {
		if (dist((*it)->getCoords(), this->getCoords()) < radius) {
			sum = sum + (*it)->getSpeedVector();
		}
	}
}

if (sum.getLength() > 0.1) {
	return sum;
} else {
	return vectorRandom.next();
}