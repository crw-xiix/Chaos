#include "pch.h"
#include "MapTile.h"
#include "AssetMgr.h"
#include "Map.h"
#include "Unit.h"
#include "GamePlayer.h"

int MapTile::getSpeed()
{

	switch (type) {
	case MapCellType::MARSH: return 3;
	case MapCellType::GRASS: return 1;
	case MapCellType::STEPPE: return 2;
	case MapCellType::HILL: return 3;
	case MapCellType::ROCKY: return 10;
	case MapCellType::DESTROYED: return 3;
	}
	//Impassable land...
	return 255;
}

MapTile::MapTile()
{

}

//Will have to figure out how to make it prettier
MapTile::MapTile(int val)
{
	imgOffset = rand() % 8;
	type = (MapCellType) val;
	speed = getSpeed();
}

MapTile::MapTile(MapCellType type)
{
	//this will work for now.....
	imgOffset = rand() % 8;
	this->type = type;
	speed = getSpeed();
}

void MapTile::Draw(SDL_Rect dest)
{
	SDL_Rect myRect;
	SDL_Texture* tempTex = AssetMgr::Get("LAND", Map::TileSize, imgOffset,(int) type, myRect);
	Display::DrawTexture(tempTex, &myRect, &dest);
	if (selected) {
		SDL_Texture* highlightTex = AssetMgr::Get("HIGHLIGHT", Map::TileSize, 0, 0, myRect);
		Display::DrawTexture(highlightTex, &myRect, &dest);

		//SDL_Texture* dude = AssetMgr::Get("UNITS", Map::TileSize, 0, 2, myRect);
		//Display::DrawTexture(dude, &myRect, &dest);
		
		//Unit dude(UnitType::Warrior);
		//dude.Draw(dest);

		GamePlayer myPlayer;
		myPlayer.GetUnits();
		
	}
}
