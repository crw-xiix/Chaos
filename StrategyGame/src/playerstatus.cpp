#include "pch.h"
#include "playerstatus.h"
#include "SDL.h"
#include "assetmgr.h"
#include "font16.h"

PlayerStatus::PlayerStatus(int x, int y, int w, int h)
{
	window = SDL_Rect{ x, y, w, h };
}

void PlayerStatus::Draw( GamePlayer &player) 
{
    // SDL_ClipRectSection myClip(window.x, window.y, window.w, window.h);

    SDL_Rect rect;
    SDL_Texture* img = AssetMgr::GetAll("PSTATUSBKG", rect);
	//Get our background up
    Display::DrawTexture(img, &rect, &window);
	//Figure out where the dudes go
	SDL_Rect destRect;
	destRect.x = window.x + 16;
	destRect.y = window.y + 5;
	destRect.w = 64;
	destRect.h = 64;

	for (auto unit : player.GetUnits())
	{
		
		unit.Draw(destRect);
		//Temp text.
		Font16::DrawText("Player Name", destRect.w + destRect.x, destRect.y + 32 - 8);
		destRect.y += destRect.h;
	}
    return;
}