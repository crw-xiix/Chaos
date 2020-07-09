#include "pch.h"
#include "map.h"
#include "perlinmap.h"

Map::Map()
{

}

void Map::Generate()
{
	PerlinMap noise(Size,Size);
	noise.Randomize(400004);
	noise.MakePerlin();
	noise.Normalize();

	for (int y = 0; y < Size; y++) {
		for (int x = 0; x < Size; x++) {
			int val =noise.GetTerrain(x, y, 9);
			
			map[y][x] = MapTile(val);
		}
	}

}

int Map::get(int x, int y)
{

	int val = map[y][x].GetTestCellVal();
	return val;
	
}

MapTile& Map::Get(int x, int y)
{
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x >= Map::Size) x = Map::Size - 1;
	if (y >= Map::Size) y = Map::Size - 1;
	return map[x][y];
}

