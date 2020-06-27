#include "pch.h"
#include "viewport.h"
#include "assetmgr.h"
#include "game.h"


ViewPort::ViewPort(int x, int y, int w, int h, float zoom)
{
	topX = x; topY = y; width = w; height = h;
	zoom = 1.0f;
	camTX = 0;
	camTY = 0;
	camX = 0;
	camY = 0;
}

void ViewPort::SetCamera(double &x, double &y)
{
	if (x < 0) x = 0;
	if (y >= 1) y = 1;
	if (x >= 1) x = 1;
	if (y <= 0) y = 0;
	camTX = x ;
	camTY = y ;
}

//Ghetto cam pan
void ViewPort::Update(int ms)
{
	float delay = 9;
	camX = ((camX*delay + camTX) / (delay+1));
	camY = ((camY*delay + camTY) / (delay+1));
}

int asdf = 0;
void ViewPort::Draw(Map& map, std::vector<GamePlayer> players, PathFinder *pathFinder)
{
	SDL_ClipRectSection myClip(topX, topY, width, height);
	SDL_Rect destRect;
	destRect.w = Map::TileSize;
	destRect.h = Map::TileSize;
	int maxXCells = width / destRect.w;
	int maxYCells = height / destRect.h;
	
	//Camera X/Y in cell grid location
	int cx = (int)(camX * Map::Size );
	int cy = (int)(camY * Map::Size );

	//Camera X/Y in pixel location
	int MScx = (int)(camX * Map::Size * Map::TileSize);
	int MScy = (int)(camY * Map::Size * Map::TileSize);
	
	//Cell grid offset from 0,0 of each cell
	int pcx = MScx % (Map::TileSize);
	int pcy = MScy % (Map::TileSize);
	
	if (cx < 0) cx = 0;
	if (cy < 0) cy = 0;
	
	int maxXCam = Map::Size - (width / Map::TileSize) -1;
	int maxYCam = Map::Size - (height / Map::TileSize) -1;

	if (cx > (maxXCam)) cx = maxXCam;
	if (cy > (maxYCam)) cy = maxYCam;
	
	for (int y = 0; y < maxYCells+2 /* scale*/; y++) {
		for (int x = 0; x < maxXCells+1/*scale*/; x++) {
			destRect.x = x * Map::TileSize + topX -pcx;
			destRect.y = y * Map::TileSize + topY -pcy;
			map.Get(cx + x, cy + y).Draw(destRect);


			//Now we need to handle the cells in the pathfinder.....
			if (pathFinder->GetRange(cx + x, cy + y) > 0) {
				SDL_Rect myRect;
				SDL_Texture* highlightTex = AssetMgr::Get("HIGHLIGHT", Map::TileSize, 0, 2, myRect);
				Display::DrawTexture(highlightTex, &myRect, &destRect);
			}

			//Highlight Current Cell under the mouse.........
			if ((Game::mCellX == (cx + x)) && ((Game::mCellY == cy + y))) {
				SDL_Rect myRect;
				SDL_Texture* highlightTex = AssetMgr::Get("HIGHLIGHT", Map::TileSize, 0, 0, myRect);
				Display::DrawTexture(highlightTex, &myRect, &destRect);
			}
		}
	}

	for (auto& player : players)
	{
		for (auto unit : player.GetUnits())
		{
			destRect.x = (unit.GetX()-cx ) * Map::TileSize + topX - pcx;
			destRect.y = (unit.GetY()-cy ) * Map::TileSize + topY - pcy;
			unit.Draw(destRect);
		}
	}
}

void ViewPort::DoSomething()
{
	///some code......................
}
/// <summary>
/// 
/// </summary>
/// <param name="mx">Mouse x</param>
/// <param name="my">Mouse y</param>
/// <param name="x">Ref OUT cell x</param>
/// <param name="y">Ref OUT cell y</param>
/// <returns>Cell location in map of map cell under cursor.....</returns>
bool ViewPort::GetCellAtMouseXY(int mx, int my, int& x, int& y)
{
	
	mx -= topX;
	my -= topY;

	mx = (int)(Map::Size*Map::TileSize * camX + mx) / Map::TileSize;
	my = (int)(Map::Size*Map::TileSize * camY + my) / Map::TileSize;

	if (camX > .1) {
		int bp = 0;
	}

	x = mx;
	y = my;

	return false;
}

void ViewPort::RenderTextureAt(int cx, int cy, int ocx, int ocy, SDL_Texture* tex, SDL_Rect* sourceRect)
{
	return;
}

bool ViewPort::MouseInViewPort(int x, int y)
{
	if (x < topX) return false;
	if (y < topY) return false;
	if (x >= (topX + width)) return false;
	if (y >= (topY + height)) return false;
	return true;
}
