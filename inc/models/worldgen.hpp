#include <cstdlib>
#include "../logger/logger.hpp"

using std::rand;
#define RAND_MAX 100
#define ROUGHNESS 0.1

class Worldgen {
public:
    static void diamondSquare(int** hmap, int size) { // size = pow(2, k) + 1
        hmap[0][0] = rand();
        hmap[size - 1][0] = rand();
        hmap[0][size - 1] = rand();
        hmap[size - 1][size - 1] = rand();
        square(0, 0, size);
        BufferedLogger logger = BufferedLogger("worldgen");
        logger.log("diamond-square started", "INFO");
    }

    static void square(int** hmap, int size, int w) { // e.g size = 257, w = 16
        BufferedLogger logger = BufferedLogger("worldgen");
        logger.log("square step with w=" + std::to_string(w), "INFO");
        for(int x=0;x<size-1;x+=w){
            for(int y=0;y<size-1;y+=w){
                hmap[x + w / 2][y + w / 2] = 100;//(hmap[x][y] + hmap[x+w][y] + hmap[x][y+w] + hmap[x+w][y+w]) / 4 + rand() * w * ROUGHNESS;
            }
        }
        if (w > 1) {
            // call the diamond step with w / 2 as w
            diamond(hmap, size, w / 2);
        }
    }

    static void diamond(int** hmap, int size, int w) {
        BufferedLogger logger = BufferedLogger("worldgen");
        logger.log("diamond step with w=" + std::to_string(w), "INFO");
        int sum, n;
        for(int x=0;x<size;x+=2*w)
            for(int y=w;y<size;y+=2*w)
            {
                sum = 0;
                n = 0;
                if (x > 0) {
                    n++;
                    sum += hmap[x-w][y];
                }
                if (y > w) {
                    n++;
                    sum += hmap[x][y-w];
                }
                if (x != size ){
                    n++;
                    sum += hmap[x+w][y];
                }
                n++;
                sum += hmap[x][y+w];

                hmap[x][y] = sum / n + rand() * ROUGHNESS * w;
            }
        for(int y=0;y<size;y+=2*w)
            for(int x=w;x<size;x+=2*w)
            {
                sum = 0;
                n = 0;
                if (y > 0) {
                    n++;
                    sum += hmap[y][x-w];
                }
                if (x > w) {
                    n++;
                    sum += hmap[x-w][y];
                }
                if (y != size ){
                    n++;
                    sum += hmap[x][y+w];
                }
                n++;
                sum += hmap[x+w][y];

                hmap[x][y] = sum / n + rand() * ROUGHNESS * w;
            }
        square(hmap, size, w);
    }
};