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

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Display::GetRenderer(), SDL_LoadBMP("assets/Example.bmp"));
	SDL_Rect texRect;
	texRect.w = 100;
	texRect.h = 100;
	texRect.x = 50;
	texRect.y = 50;

	PerlinMap map = PerlinMap(10, 10, 99);
	map.Randomize();
	float v = map.getTestValue();


	while (Game::IsRunning())
	{
		Game::ProcessEvents();

		Display::Clear(255, 0, 0);
		Display::DrawTexture(texture, &texRect);
		Display::Present();
	}

	SDL_Quit();
	return 0;
}