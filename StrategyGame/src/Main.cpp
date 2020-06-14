#include "pch.h"
#include "Display.h"
#include "Game.h"
#include "PerlinMap.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to init SDL " << SDL_GetError() << "\n";
		return -1;
	}
	
	Game::Create();
	Display::Create(720, 480);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Display::GetRenderer(), SDL_LoadBMP("assets/ColorExample.bmp"));
	SDL_Rect texRect;
	texRect.w = 100;
	texRect.h = 100;
	texRect.x = 50;
	texRect.y = 50;

	SDL_Rect subTex;
	subTex.w = 100;
	subTex.h = 100;
	subTex.x = 522;
	subTex.y = 50;

	



	while (Game::IsRunning())
	{
		Game::ProcessEvents();

		Display::Clear(255, 0, 0);
		//RW test func
		

		Display::DrawTexture(texture, &texRect, &subTex);
		PerlinMap::TestDraw();
		Display::Present();
	}

	SDL_Quit();
	return 0;
}