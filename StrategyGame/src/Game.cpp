#include "pch.h"
#include "Game.h"

Game::Game()
	: running(true)
{
}

Game::~Game()
{
	delete gameInstance;
}

void Game::Create()
{
	gameInstance = new Game();
}

void Game::ProcessEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			gameInstance->running = false;
		}
	}
}

/*private static members*/
Game* Game::gameInstance;