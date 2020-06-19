#include "pch.h"
#include "viewport.h"
#include "AssetMgr.h"


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
	if (x < 0) x = 0;
	if (y >= 1) y = 1;

	camTX = x ;
	camTY = y ;

	
}

//Ghetto cam pan
void ViewPort::Update(int ms)
{
	camX = ((camX*4 + camTX) / 5.0);
	camY = ((camY*4 + camTY) / 5.0);
}

int asdf = 0;
void ViewPort::Draw(Map& map, std::vector<Unit> units)
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
		}
	}
}

void ViewPort::DoSomething()
{
	///some code......................
}

bool ViewPort::GetCellAtMouseXY(int mx, int my, int& x, int& y)
{
	x = 0;
	y = 0;
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
