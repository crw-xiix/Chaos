#include "pch.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
	{
		SDL_Log("Failed to init SDL: %s", SDL_GetError());
		return -1;
	}

	SDL_Log("Hello World!");

	return 0;
}