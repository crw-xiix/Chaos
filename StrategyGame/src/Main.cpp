#include "pch.h"
#include "Display.h"
#include "Game.h"
#include "PerlinMap.h"
#include <SDL_image.h>
#include <AssetMgr.h>
#include "Map.h"


int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to init SDL " << SDL_GetError() << "\n";
		return -1;
	}
	
	Game::Create();
	Display::Create(1800, 1000);
	IMG_Init(IMG_INIT_PNG);
	SDL_Texture* texture = IMG_LoadTexture(Display::GetRenderer(), "assets/landscape.png");
	
	//SDL_Texture* texture = SDL_CreateTextureFromSurface(Display::GetRenderer(), IMG_LoadTexture(Display::GetRenderer(), "assets/landscape.png"));
	SDL_Rect texRect;
	texRect.w = 256;
	texRect.h = 512;
	texRect.x = 0;
	texRect.y = 0;

	SDL_Rect subTex;
	subTex.w = 256;
	subTex.h = 256;
	subTex.x = 512;
	subTex.y = 256;

	Map GameMap;
	GameMap.Generate();

	AssetMgr::Load("assets/landscape.png", "LAND");
	int cx = 0;
	int cy = 0;
	int scale = 3;
	while (Game::IsRunning())
	{
		Game::ProcessEvents();
		Display::Clear(0, 0, 0);

		//RW test proc - there is no real range checking so relax.........
		const uint8_t* ks = SDL_GetKeyboardState(NULL);
		if (ks[SDL_SCANCODE_W]) cy--;
		if (ks[SDL_SCANCODE_S]) cy++;
		if (ks[SDL_SCANCODE_A]) cx--;
		if (ks[SDL_SCANCODE_D]) cx++;

		if (cx < 0) cx = 0;
		if (cy < 0) cy = 0;

		SDL_Rect destRect;
		destRect.w = 32/scale;
		destRect.h = 32/scale;
		for (int y = 0; y < 32*scale; y++) {
			for (int x = 0; x < 55*scale; x++) {
				destRect.x = x * 32/scale;
				destRect.y = y * 32/scale;
				SDL_Rect myRect;
				//messy, but just a test...  tx = texture x
				int tx = GameMap.GetOfs(cx+x, cy+y);
				int ty = GameMap.get(cx+x, cy+y);
				SDL_Texture* tempTex = AssetMgr::Get("LAND",32,tx,ty,myRect);
				Display::DrawTexture(tempTex,&myRect, &destRect);
			}
		}
		//END RW test func

		
//		Display::DrawTexture(texture, &texRect, &subTex);  //Dis test func
		Display::Present();
	}
	AssetMgr::Destroy();
	SDL_Quit();
	return 0;
}