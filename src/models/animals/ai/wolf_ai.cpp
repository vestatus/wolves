// тут не надо писать никаких функций, этот файл -- уже кусок тела функции src/models/ai.cpp/decideWhereToGo

float hare_dist=100500;
float wolf_dist=100500;
float d;
Animal* nearest_hare = nullptr;
Animal* nearest_wolf = nullptr;

for(auto it=begin(); it != end(); it++) {
	d = hypot(x - (*it)->getX(), y - (*it)->getY());
	if ((*it)->isHare() && (d < hare_dist)) {
		hare_dist = d;
		nearest_hare = (*it);
	} else if ((*it)->isWolf() && (d < wolf_dist) && (*it != this)) {
		wolf_dist = d;
		nearest_wolf = (*it);
	} 
}

if ((age > MIN_BREEDING_AGE ) && (hunger < MAX_BREEDING_HUNGER) && (nearest_wolf != nullptr)) return pair<float, float>(nearest_wolf->getX() - x, nearest_wolf->getY() - y);

if (nearest_hare == nullptr) {
	return pair<float, float>(0, 0);
} else {
	return pair<float, float>(nearest_hare->getX() - x, nearest_hare->getY() - y);
}