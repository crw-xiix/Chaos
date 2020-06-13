#pragma once


class PerlinMap {
private:
	int seed = 0;
	int width = 0;
	int height = 0;
	float* svalues = nullptr;
	float* evalues = nullptr;

public:
	PerlinMap(int x, int y, unsigned long seed) {
		width = x;
		height = y;
		this->seed = seed;
		evalues = new float[x * y];
		svalues = new float[x * y];
	}

	void Randomize() {
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < width; y++) {
				//svalues[y*width+x] = rand

			}
		}
	}

	


};