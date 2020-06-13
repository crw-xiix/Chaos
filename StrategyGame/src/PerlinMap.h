#pragma once


class PerlinMap {
private:
	int seed = 0;
	int width = 0;
	int height = 0;
	float* svalues = nullptr;
	float* evalues = nullptr;

public:
	PerlinMap(int x, int y, unsigned long seed);
	~PerlinMap();

	void Randomize();
	float getTestValue();
};