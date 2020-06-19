#include "pch.h"
#include "Game.h"
#include "AssetMgr.h"
#include "viewport.h"


Game::Game()
	: running(true)
{
}

Game::~Game()
{
	delete gameInstance;
}

//static
void Game::Create()
{
	gameInstance = new Game();
}

//static
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

void Game::Process() {
	Display::Clear(0, 0, 0);

	
	const uint8_t* ks = SDL_GetKeyboardState(NULL);
	if (ks[SDL_SCANCODE_W]) cy -= 0.001;
	if (ks[SDL_SCANCODE_S]) cy += 0.001;
	if (ks[SDL_SCANCODE_A]) cx -= 0.001;
	if (ks[SDL_SCANCODE_D]) cx += 0.001;
	
	viewPort.SetCamera(cx, cy);
	viewPort.Update(1);
	SDL_Rect myRect;

	//Get the background up there.........
	SDL_Texture* tempTex = AssetMgr::GetAll("BKG", myRect);
	SDL_Rect screen = { 0,0,1600,800 };
	SDL_RenderSetClipRect(Display::GetRenderer(), &screen);
	Display::DrawTexture(tempTex, &myRect, &screen);

	//Draw the map
	viewPort.Draw(*gameMap, units);
	//Draw the UI......
}

void Game::StartUp(int x, int y)
{
	gameMap = new Map();
	gameMap->Generate();

	AssetMgr::Load("assets/landscape.png", "LAND");
	AssetMgr::Load("assets/background.png", "BKG");
	AssetMgr::Load("assest/dudes.png", "UNITS");

	//These numbers come from the background image........
	viewPort = ViewPort(325, 75, 1225, 675, 1.0f);
	

}

/*private static members*/
Game* Game::gameInstance;