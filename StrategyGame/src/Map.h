#pragma once

#include "MapTile.h"

class Map {
public:
	static constexpr int Size = 128;  //Need a power of 2......
	static constexpr int TileSize = 64;
	static int nogConstant;
private:
	MapTile map[Size][Size];
public:
	Map();

	void Generate();
	int get(int x, int y);
	MapTile Get(int x, int y);
	inline int GetOfs(int x, int y) {
		return map[x][y].GetTestCellOfs();
	}

};
