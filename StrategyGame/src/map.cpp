#include "pch.h"
#include "Map.h"
#include "PerlinMap.h"

Map::Map()
{

}

void Map::Generate()
{
	PerlinMap noise(Size,Size);
	noise.Randomize(400000);
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

MapTile Map::Get(int x, int y)
{
	return map[x][y];
}


 int Map::nogConstant = 2;