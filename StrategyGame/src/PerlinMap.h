#pragma once



/// <summary>
/// Do not use new on this.  Just put it on the stack.  Loop through until paths are verified, then go out of scope.
/// </summary>
class PerlinMap {
private:
	int seed = 0;
	int width = 0;
	int height = 0;
	float* svalues = nullptr;
	float* evalues = nullptr;
	const int octaves = 6;
public:
	PerlinMap(int x, int y);
	~PerlinMap();
	/// <summary>
	/// Randomizes the source numbers, taking a new seed - if 
	/// </summary>
	void Randomize(int seed);
	void MakePerlin();
	void Normalize();
	//this will be enum soon
	int GetTerrain(int x, int y, int max);
	static void TestDraw();
};