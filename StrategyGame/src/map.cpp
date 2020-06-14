#include "pch.h"
#include "map.h"
#include "PerlinMap.h"


Map::Map()
{
	PerlinMap generator  = PerlinMap(Size, Size);
	//xxxc adjust seed later.........
	generator.Randomize(108);
	generator.Normalize();

	for (int y = 0; y < Size; y++) {
		for (int x = 0; x < Size; x++) {
			map[y][x] = MapTile((MapCellType) generator.GetTerrain(x, y, 8));
		}
	}
}
