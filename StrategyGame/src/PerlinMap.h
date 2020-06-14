#pragma once

class PerlinMap {
private:
	int seed = 0;
	int width = 0;
	int height = 0;
	float* svalues = nullptr;
	float* evalues = nullptr;
	const int octaves = 6;
public:
	PerlinMap(int x, int y, unsigned long seed);
	~PerlinMap();
	void Randomize();
	void MakePerlin();
	void Normalize();
	//this will be enum soon
	int GetTerrain(int x, int y, int max);
	static void TestDraw();
};