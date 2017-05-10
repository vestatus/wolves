#pragma once
#include "../tools/containers.hpp"
#include <cmath>
#include <vector>

using std::vector;

class HSV_to_RGB {
public:

	struct rgb{
	    double r;       // a fraction between 0 and 1
	    double g;       // a fraction between 0 and 1
	    double b;       // a fraction between 0 and 1
	};

	struct hsv{
	    double h;       // angle in degrees
	    double s;       // a fraction between 0 and 1
	    double v;       // a fraction between 0 and 1
	};

	static hsv rgb2hsv(rgb in);
	static rgb hsv2rgb(hsv in);
};

float dist(pair<float, float> a, pair<float, float> b);

vector<pair<float, float>> getCircleOfAngledVectors(int num);