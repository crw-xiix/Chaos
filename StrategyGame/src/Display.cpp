#include "pch.h"
#include "Display.h"

Display::Display(int width, int height)
	: window(nullptr), renderer(nullptr), width(width), height(height)
{
	if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0)
	{
		std::cout << "Failed to create display: " << SDL_GetError() << "\n";
	}
}

Display::~Display()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	delete displayInstance;
}

void Display::Create(int width, int height)
{
	displayInstance = new Display(width, height);
}

void Display::Clear(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetRenderDrawColor(GetRenderer(), r, g, b, 255);
	SDL_RenderClear(GetRenderer());
}

void Display::Present()
{
	SDL_RenderPresent(GetRenderer());
}

void Display::DrawTexture(SDL_Texture* texture)
{
	SDL_RenderCopy(GetRenderer(), texture, nullptr, nullptr);
}

void Display::DrawTexture(SDL_Texture* texture, const SDL_Rect* targetRect)
{
	SDL_RenderCopy(GetRenderer(), texture, nullptr, targetRect);
}

/*Static members*/
Display* Display::displayInstance;