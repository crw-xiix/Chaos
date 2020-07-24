#pragma once
#include "gameplayer.h"

class PlayerStatus
{
	
private:
	std::list<std::string> data;
	SDL_Rect window;
	int maxLines = 10;
public:
	PlayerStatus(int x, int y, int w, int h);

	void Draw(GamePlayer &player);
};

