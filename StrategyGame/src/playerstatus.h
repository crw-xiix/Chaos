#pragma once
#include "gameplayer.h"

class PlayerStatus
{
public:
	PlayerStatus(int x, int y, int w, int h);
	/// <summary>
	/// Draws a player....
	/// </summary>
	/// <param name="player"></param>
	void Draw(GamePlayer &player);
private:
	SDL_Rect window;
};

