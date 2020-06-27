#pragma once

#include "maptile.h"

class Map {
public:
	friend class PathFind;
	static constexpr int Size = 128;  //Need a power of 2......
	static constexpr int TileSize = 64;
private:
	MapTile map[Size][Size];
public:
	Map();
	void Generate();
	int get(int x, int y);
	MapTile& Get(int x, int y);
	//Stuff to get/set later
	bool highlighted = false;
};
