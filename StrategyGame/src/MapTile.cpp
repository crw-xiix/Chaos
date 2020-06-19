#include "pch.h"
#include "MapTile.h"

MapTile::MapTile()
{

}

//Will have to figure out how to make the prettier
MapTile::MapTile(int val)
{
	imgOffset = rand() % 8;
	type = (MapCellType) val;
}

MapTile::MapTile(MapCellType type)
{
	//this will work for now.....
	imgOffset = rand() % 8;
	this->type = type;
}

void MapTile::Draw(int x, int y)
{

	//nothing yet.......
}
