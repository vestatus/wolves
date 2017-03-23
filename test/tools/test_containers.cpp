#include <iostream>
#include <cstdio>
#include "../../src/tools/containers.hpp"

int main() {
	Array2DKeeper<int> keeper(10, 20);
	for (int i=0;i<10;i++) for(int j=0;j<20;j++)
		keeper.getArray2D()[i][j] = i * j;
	
	for (int i=0;i<10;i++) for(int j=0;j<20;j++)
		std::cout << keeper.getArray2D()[i][j] << " ";
	
	return 0;
}
