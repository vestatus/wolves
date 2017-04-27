// тут не надо писать никаких функций, этот файл -- уже кусок тела функции src/models/ai.cpp/decideWhereToGo

float dist=100500;
float d;
Animal* nearest = nullptr;

for(auto it=begin(); it != end(); it++) {
	d = hypot(x - (*it)->getX(), y - (*it)->getY());
	if ((*it)->isHare() && (d < dist)) {
		dist = d;
		nearest = (*it);
	}
}

if (nearest == nullptr) {
	return pair<float, float>(0, 0);
} else {
	return pair<float, float>(nearest->getX() - x, nearest->getY() - y).scale(1);
}