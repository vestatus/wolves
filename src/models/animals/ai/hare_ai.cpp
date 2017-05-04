const int radius = 100;

int SAMPLING_DIST = 100 * hunger / maxHunger;
pair <float, float> coords = getCoords();
pair<float, float> bestDir(0, 0);
int maxScore = -100500;

vector<pair<float, float>> samples = getCircleOfAngledVectors(10);

for (auto v=samples.begin(); v!= samples.end(); v++) {
	pair<float, float> vec_rel = (*v).scale(SAMPLING_DIST);
	pair<float, float> vec = coords + vec_rel;
	int score = 0;

	if ((vec.a < 0) || (vec.b < 0) || (vec.a >= world->width) || (vec.b >= world->height)) score = -1000;
	else {
		if (world->isLandAt(vec.a, vec.b)) {
			score += world->cutGrass(vec.a, vec.b, 2, 10000, false);
			//cout << score << "\n";
		} else {
			score -= 100;
		}
	}

	for(auto it=begin();it!=end();it++) {
		if ((*it)->isWolf() && (*it)->isAlive() && (dist(vec, (*it)->getCoords()) < radius)) {
			score -= (int)(10000 / dist(vec, (*it)->getCoords()));
			// cout << "penalty = " << (int)(10000 / dist(vec, (*it)->getCoords())) << "\n";
		}
	}

	//cout << vec_rel.a << ";" << vec_rel.b << " " << score << "\n";

	if (score > maxScore) {
		maxScore = score;
		bestDir = vec_rel;
	}
}

// cout << "chose " << maxScore << "\n";
// cout << "====================\n";

return bestDir.scale(1);// + vectorRandom.next().scale(1);