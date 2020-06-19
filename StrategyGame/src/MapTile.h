#pragma once
#include "pch.h"

enum class MapCellType {
	DEEP_SEA = 0,
	WATER,
	MARSH,
	GRASS,
	STEPPE,
	HILL,
	ROCKY,
	SNOW,
	NONE,
	DESTROYED
};

//This is a location on the map, stored inside the map
class MapTile {
private:
	MapCellType type = MapCellType::NONE;
	int imgOffset = 0;
public:
	MapTile();
	MapTile(int val);
	MapTile(MapCellType type);
	void Draw(SDL_Rect dest);
	inline int GetTestCellVal() { return (int)type; }
	inline int GetTestCellOfs() { return imgOffset; }

};
