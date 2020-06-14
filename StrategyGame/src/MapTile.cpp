#include "pch.h"
#include "MapTile.h"

MapTile::MapTile()
{

}

MapTile::MapTile(MapCellType type)
{
	//this will work for now.....
	imgOffset = rand() % 8;
}

void MapTile::Draw(int x, int y)
{
	//nothing yet.......
}
