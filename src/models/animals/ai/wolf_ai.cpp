// тут не надо писать никаких функций, этот файл -- уже кусок тела функции src/models/ai.cpp/decideWhereToGo

float hare_dist=100500;
float wolf_dist=100500;
float d;
Animal* nearest_hare = nullptr;
Animal* nearest_wolf = nullptr;

const int MIN_CHASING_HUNGER = MAX_BREEDING_HUNGER;
const int MAX_CLUSTER_DIST = 40;
const int MIN_CLUSTER_DIST = 5;
const int DESIRED_CLUSTER_SIZE = 5;
bool UNCOMFORTABLY_CLOSE = false;
pair<float, float> outOfCluster(0, 0);
int wolvesAround = 0;

for(auto it=begin(); it != end(); it++) {
	d = hypot(x - (*it)->getX(), y - (*it)->getY());
	if ((*it)->isHare() && (d < hare_dist) && (world->isLandAt((*it)->getX(), (*it)->getY()))) {
		hare_dist = d;
		nearest_hare = (*it);
	} else if ((*it)->isWolf() && (*it != this)) {
		if (d < wolf_dist) {
			wolf_dist = d;
			nearest_wolf = (*it);
		}
		if (d < MAX_CLUSTER_DIST) wolvesAround++;
		if (d < MIN_CLUSTER_DIST) {
			outOfCluster = outOfCluster + - pair<float, float>((*it)->getX() - x, (*it)->getY() - y).scale(1);
			UNCOMFORTABLY_CLOSE = true;
		}
	}
}
if ((age > MIN_BREEDING_AGE) && (hunger < MAX_BREEDING_HUNGER)) UNCOMFORTABLY_CLOSE = false;
if (UNCOMFORTABLY_CLOSE && (world->isLandAt(getCoords() + outOfCluster * 10))) return outOfCluster;

if ((age > MIN_BREEDING_AGE ) && (hunger < MAX_BREEDING_HUNGER) && (nearest_wolf != nullptr)) 
	return pair<float, float>(nearest_wolf->getX() - x, nearest_wolf->getY() - y);

if (((target == nullptr) || (! target->isAlive())) && (hunger < MIN_CHASING_HUNGER) && (nearest_hare != nullptr)) {
	target = nearest_hare;
}

if ((target == nullptr) || (hunger < MIN_CHASING_HUNGER)) {
	if ((nearest_wolf != nullptr) && (wolvesAround < DESIRED_CLUSTER_SIZE) && (wolf_dist > MAX_CLUSTER_DIST)) {
		return pair<float, float>(nearest_wolf->getX() - x, nearest_wolf->getY() - y);
	}
	else if (nearest_hare == nullptr) {
		return pair<float, float>(0, 0);
	} else {
		return pair<float, float>(nearest_hare->getX() - x, nearest_hare->getY() - y);
	}
} else if (nearest_hare != nullptr) {
	return pair<float, float>(nearest_hare->getX() - x, nearest_hare->getY() - y);
}

return vectorRandom.next();