#pragma once
#include <list>

using std::list;

class Wolf {
protected:
	static list<Wolf> wolves;
	int hunger;
	int x, y;
public:
	Wolf();
	int getSpeed();
};