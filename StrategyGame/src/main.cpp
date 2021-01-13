#include "pch.h"
#include "display.h"
#include "game.h"
#include "perlinmap.h"
#include <SDL_image.h>
#include "assetmgr.h"
#include "map.h"
#include "viewport.h"
//#include "../3rd/easywsclient.hpp"

#include <assert.h>
#include <stdio.h>
#include <string>
#include <memory>
#include "unit.h"
#include "../3rd/jute.h"




int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to init SDL " << SDL_GetError() << "\n";
		return -1;
	}

	Display::Create(1600, 800);
	IMG_Init(IMG_INIT_PNG);

	//Get our stuff loaded up
	AssetMgr::Load("assets/landscape.png", "LAND");
	AssetMgr::Load("assets/background.png", "BKG");
	AssetMgr::Load("assets/Dudes.png", "UNITS");
	AssetMgr::Load("assets/highlights.png", "HIGHLIGHT");
	AssetMgr::Load("assets/font16.png", "FONT16");
	AssetMgr::Load("assets/intro.png", "INTRO");
	AssetMgr::Load("assets/menubkg.png", "MENUBKG");
	AssetMgr::Load("assets/button.png", "BUTTON");
	AssetMgr::Load("assets/playerstatusbackground.png", "PSTATUSBKG");

	Game::Create();
	Game::gameInstance->StartUp(1600, 800);

	Uint64 now, last;
	now = SDL_GetPerformanceCounter();

	while (Game::IsRunning())
	{
		//Handle our timing
		last = now;
		now = SDL_GetPerformanceCounter();
		double deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());
		Game::ProcessEvents();
        if (!Game::gameInstance->Process(deltaTime)) break;
		Game::gameInstance->Draw(deltaTime);
		Display::Present();
		SDL_Delay(1);
	}
	//Game::Destroy();
	AssetMgr::Destroy();
	SDL_Quit();
	_CrtDumpMemoryLeaks();
	return 0;
}
