#include "pch.h"
#include "MapTile.h"
#include "AssetMgr.h"
#include "Map.h"

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

void MapTile::Draw(SDL_Rect dest)
{
	SDL_Rect myRect;
	SDL_Texture* tempTex = AssetMgr::Get("LAND", Map::TileSize, imgOffset,(int) type, myRect);
	Display::DrawTexture(tempTex, &myRect, &dest);
}
