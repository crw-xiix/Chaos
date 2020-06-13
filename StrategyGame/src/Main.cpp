#include "pch.h"
#include "Display.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to init SDL " << SDL_GetError() << "\n";
		return -1;
	}
	
	Display::Create(720, 480);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Display::GetRenderer(), SDL_LoadBMP("assets/Example.bmp"));
	SDL_Rect texRect;
	texRect.w = 100;
	texRect.h = 100;
	texRect.x = 50;
	texRect.y = 50;

	while (true)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				SDL_Quit();
				return 0;
			}
		}

		Display::Clear(255, 0, 0);
		Display::DrawTexture(texture, &texRect);
		Display::Present();
	}

	return 0;
}