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
}