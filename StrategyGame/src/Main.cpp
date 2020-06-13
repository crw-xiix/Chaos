#include "pch.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("SDL initialization failed... %s", SDL_GetError());
	}

	return 0;
}