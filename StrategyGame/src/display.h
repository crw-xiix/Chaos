#pragma once
#include "pch.h"

class Display
{
private:
	static Display* displayInstance;

	SDL_Window* window;
	SDL_Renderer* renderer;

	Display(int width, int height);
	~Display();

public:
	static int Width;
	static int Height;

	static void Create(int width, int height);

	static void Clear(Uint8 r, Uint8 g, Uint8 b);
	static void Present();
	
	static void DrawTexture(SDL_Texture* texture);
	static void DrawTexture(SDL_Texture* texture, const SDL_Rect* targetRect);
	static void DrawTexture(SDL_Texture* texture, const SDL_Rect* targetRect, const SDL_Rect* subTexture);

	static inline SDL_Window* GetWindow() { return displayInstance->window; }
	static inline SDL_Renderer* GetRenderer() { return displayInstance->renderer; }
};


class SDL_ClipRectSection {
	SDL_Rect oldRect;
public:
	SDL_ClipRectSection(int x, int y, int w, int h);
	~SDL_ClipRectSection(); 
};