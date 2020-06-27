#pragma once
#include "pch.h"

enum class MapCellType {
	DEEP_SEA = 0,
	WATER,
	SHALLOW_WATER,
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
	friend class PathFind;
	int speed = 99;
	int getSpeed();
public:
	bool selected = false;
	MapTile();
	MapTile(int val);
	MapTile(MapCellType type);
	void Draw(SDL_Rect dest);
	inline int GetTestCellVal() { return (int)type; }
	inline int GetTestCellOfs() { return imgOffset; }
	inline int GetSpeed() { return speed; }

};
