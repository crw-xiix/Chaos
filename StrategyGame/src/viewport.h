#pragma once
#include "pch.h"
#include <Map.h>
#include <Unit.h>
#include "GamePlayer.h"

class ViewPort {
private:
	int topX, topY;
	int width, height;
	float zoom = 1.0f;
	//Camera Location
	double camX, camY;  
	double camTX, camTY;
public:
	ViewPort(int x, int y, int w, int h, float zoom);
	ViewPort() = default;
	
	void SetCamera(double& x, double& y);
	void Update(int ms);
	void Draw(Map& map, std::vector<GamePlayer> players);
	void DoSomething();
	bool GetCellAtMouseXY(int mx, int my, int& x, int& y);
	void RenderTextureAt(int cx, int cy, int ocx, int ocy, SDL_Texture* tex, SDL_Rect* sourceRect);
	bool MouseInViewPort(int x, int y);






};
