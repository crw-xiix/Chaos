#include "pch.h"
#include "Display.h"
#include "Game.h"
#include "PerlinMap.h"
#include <SDL_image.h>


int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to init SDL " << SDL_GetError() << "\n";
		return -1;
	}
	
	Game::Create();
	Display::Create(720, 480);
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

	



	while (Game::IsRunning())
	{
		Game::ProcessEvents();

		Display::Clear(0, 0, 0);
		//RW test func
		

		Display::DrawTexture(texture, &texRect, &subTex);
		PerlinMap::TestDraw();
		Display::Present();
	}

	SDL_Quit();
	return 0;
}