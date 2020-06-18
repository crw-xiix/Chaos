#include "pch.h"
#include "Display.h"
#include "Game.h"
#include "PerlinMap.h"
#include <SDL_image.h>
#include <AssetMgr.h>
#include "Map.h"
#include "viewport.h"


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

	Map* gameMap = new Map();
	gameMap->Generate();

	AssetMgr::Load("assets/landscape.png", "LAND");
	double cx = 0;
	double cy = 0;
	int scale = 1;
	ViewPort vp(50, 50, 1600, 800, 1.0f);
	std::vector<Unit> units;

	while (Game::IsRunning())
	{
		Game::ProcessEvents();
		Display::Clear(0, 0, 0);

		//RW test proc - there is no real range checking so relax.........
		const uint8_t* ks = SDL_GetKeyboardState(NULL);
		if (ks[SDL_SCANCODE_W]) cy-= 0.001;
		if (ks[SDL_SCANCODE_S]) cy += 0.001; 
		if (ks[SDL_SCANCODE_A]) cx -= 0.001; 
		if (ks[SDL_SCANCODE_D]) cx += 0.001;
		
		
		vp.SetCamera(cx, cy);
		vp.Update(1);
		vp.Draw(*gameMap, units);
		
		//END RW test func

//		Display::DrawTexture(texture, &texRect, &subTex);  //Dis test func
		Display::Present();
		SDL_Delay(11);
	}
	AssetMgr::Destroy();
	SDL_Quit();
	return 0;
}