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

	int mx, my;

	
	SDL_GetMouseState(&mx, &my);
	
	viewPort.SetCamera(cx, cy);
	viewPort.Update(1);
	SDL_Rect myRect;

	//Get the background up there.........
	SDL_Texture* tempTex = AssetMgr::GetAll("BKG", myRect);
	SDL_Rect screen = { 0,0,1600,800 };
	SDL_RenderSetClipRect(Display::GetRenderer(), &screen);
	Display::DrawTexture(tempTex, &myRect, &screen);
	//Ref out for mCell*
	viewPort.GetCellAtMouseXY(mx, my, mCellX, mCellY);

	//Draw the map
	viewPort.Draw(*gameMap, players, pathFinder);
	//Draw the UI......
}

void Game::StartUp(int x, int y)
{
	gameMap = new Map();
	gameMap->Generate();

	pathFinder = new PathFinder(*gameMap);

	AssetMgr::Load("assets/landscape.png", "LAND");
	AssetMgr::Load("assets/background.png", "BKG");
	AssetMgr::Load("assets/dudes.png", "UNITS");
	AssetMgr::Load("assets/highlights.png", "HIGHLIGHT");

	//These numbers come from the background image........
	viewPort = ViewPort(325, 75, 1225, 675, 1.0f);
	/*
	gameMap->Get(10, 12).selected = true;
	*/
	GamePlayer player;
	players.push_back(player);


	pathFinder->DoUnitMaxDistanceTravel(players[0].GetUnit(0), 20);
}

/*private static members*/
Game* Game::gameInstance;

int Game::mCellX = 5;
int Game::mCellY = 5;