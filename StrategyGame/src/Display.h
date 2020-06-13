#pragma once
#include "pch.h"

class Display
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	int width;
	int height;

public:
	Display(int width, int height);
	~Display();

	inline SDL_Window* GetWindow() const { return window; }
	inline SDL_Renderer* GetRenderer() const { return renderer; }
};