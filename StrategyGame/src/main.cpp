#include "pch.h"
#include "display.h"
#include "game.h"
#include "perlinmap.h"
#include <SDL_image.h>
#include "assetmgr.h"
#include "map.h"
#include "viewport.h"


int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to init SDL " << SDL_GetError() << "\n";
		return -1;
	}

	Game::Create();
	Display::Create(1600, 800);
	IMG_Init(IMG_INIT_PNG);

	Game::gameInstance->StartUp(1600, 800);

	while (Game::IsRunning())
	{
		Game::ProcessEvents();
		Game::gameInstance->Process();
		Display::Present();
		SDL_Delay(11);
	}
	AssetMgr::Destroy();
	SDL_Quit();
	return 0;
}