#pragma once
#include "pch.h"
#include "map.h"
#include "unit.h"
#include "gameplayer.h"
#include "pathfind.h"

class ViewPort {
private:
	int topX=0, topY=0;
	int width=0, height=0;
	float zoom = 1.0f;
	//Camera Location
	double camX=0.0, camY=0.0;  
	double camTX=0.0, camTY=0.0;
public:
	ViewPort(int x, int y, int w, int h, float zoom);
	ViewPort() = default;
	
	void SetCamera(double& x, double& y);
	void Update(int ms);
	void Draw(Map& map, std::vector<GamePlayer> players, PathFinder *pathFinder);
	void DoSomething();
	bool GetCellAtMouseXY(int mx, int my, int& x, int& y);
	void RenderTextureAt(int cx, int cy, int ocx, int ocy, SDL_Texture* tex, SDL_Rect* sourceRect);
	bool MouseInViewPort(int x, int y);






};
