#include "../../inc/tools/worldgen.hpp"

WorldGenerator::WorldGenerator(int size, int seed) {
	this->size = size;
	this->seed = seed;
	this->random.init(-500, 500, seed);
}

WorldGenerator::~WorldGenerator() {

}

void WorldGenerator::square(int** hmap, int w) {
	int sum;

	for(int x = 0;x < size - 1; x += w) {
		for(int y = 0;y < size - 1; y += w) {
			sum = hmap[x][y] + hmap[x + w][y] + hmap[x][y + w] + hmap[x + w][y + w];

			hmap[x + w / 2][y + w / 2] = sum / 4 + int(w * 0.707 * R * random.next());
		}
	}

	diamond(hmap, w);
}

void WorldGenerator::smoothe(int** hmap) {
	int res[size][size];
	int n, sum;
	int nb_imp = 1; // each neigbour is np_imp times as important as the cell itself

	for (int x = 0; x < size; x++)
		for (int y = 0;y < size; y++) {
			n = 2;
			sum = hmap[x][y];

			if (x > 0) {sum += nb_imp * hmap[x - 1][y]; n += nb_imp;}
			if (y > 0) {sum += nb_imp * hmap[x][y - 1]; n += nb_imp;}
			if (x < size - 1) {sum += nb_imp * hmap[x + 1][y]; n += nb_imp;}
			if (y < size - 1) {sum += nb_imp * hmap[x][y + 1]; n += nb_imp;}

			res[x][y] = sum / n;
		}

	for (int x = 0; x < size; x++)
		for (int y = 0;y < size; y++) hmap[x][y] = res[x][y];
}

void WorldGenerator::diamond(int** hmap, int w) {
	int k = 0; // row counter
	int start, sum, n;

	for(int y = 0; y < size; y += w / 2) { // no mistake here, not size - 1, but size
		start = ((k + 1) % 2) * w / 2;

		for (int x = start; x < size; x += w) {
			n = 0;
			sum = 0;

			if (x > 0) {sum += hmap[x - w/2][y]; n++;}
			if (y > 0) {sum += hmap[x][y - w/2]; n++;}
			if (x < size - 1) {sum += hmap[x + w/2][y]; n++;}
			if (y < size - 1) {sum += hmap[x][y + w/2]; n++;}

			hmap[x][y] = sum / n + int(w * 0.5 * R * random.next());
		}

		k++;
	}

	if (w > 2) square(hmap, w / 2);
}

void WorldGenerator::generate(int** hmap) {
	hmap[0][0] = -100;
	hmap[0][size - 1] = -100;
	hmap[size - 1][0] = -100;
	hmap[size - 1][size - 1] = -100;

	square(hmap, size - 1);

	smoothe(hmap);
}
