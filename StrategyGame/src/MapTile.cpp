#include "pch.h"
#include "MapTile.h"
#include "AssetMgr.h"
#include "Map.h"

MapTile::MapTile()
{

}

//Will have to figure out how to make it prettier
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
	if (selected) {
		SDL_Texture* highlightTex = AssetMgr::Get("HIGHLIGHT", Map::TileSize, 0, 0, myRect);
		Display::DrawTexture(highlightTex, &myRect, &dest);
		SDL_Texture* dude = AssetMgr::Get("UNITS", Map::TileSize, 0, 0, myRect);
		Display::DrawTexture(dude, &myRect, &dest);
	}
}
