#pragma once

#include "Map.h"
#include "MapTile.h"


class Map {
public:
	static constexpr int Size = 128;  //Need a power of 2......
private:
	MapTile map[Size][Size];
public:
	Map();
};
