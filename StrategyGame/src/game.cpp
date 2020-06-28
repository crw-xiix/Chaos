#include "pch.h"
#include "game.h"
#include "assetmgr.h"
#include "viewport.h"


Game::Game()
	: running(true)
{

}

Game::~Game()
{
	delete gameInstance;
}

void Game::handleMouse()
{

	int mx, my;
	uint32_t mouseState = SDL_GetMouseState(&mx, &my);
	//Update the hover locations
	viewPort.GetCellAtMouseXY(mx, my, mCellX, mCellY);

	bool tMouseDown = mouseState & SDL_BUTTON_LEFT;
	if (tMouseDown != mouseDown) {   //State changed.
		if (tMouseDown) {
			viewPort.GetCellAtMouseXY(mx, my, lastMouseCell.x, lastMouseCell.y);
		}
		else { //Upclick
			int imx, imy;
			viewPort.GetCellAtMouseXY(mx, my, imx, imy);
			if ((imx == lastMouseCell.x) && (imy = lastMouseCell.y)) {
				click();
				lastMouseCell.x = -1;
				lastMouseCell.y = -1;
			}
		}
		mouseDown = tMouseDown;
	}
}

void Game::click()
{
	int sp, su;
	if (getCharacterAt(lastMouseCell.x, lastMouseCell.y, sp, su)) {
		//We have a character......
		int bp = 0;
		if (sp == curPlayer) {
			if (su != selUnit) {
				selectUnit(sp, su);
			};
		}
	}
	else {
		if (pathFinder->GetRange(lastMouseCell.x, lastMouseCell.y) > -1) {
			//This should be a valid move.
			auto& thisUnit = players[curPlayer].GetUnit(selUnit);
			thisUnit.Move(lastMouseCell.x, lastMouseCell.y);
			int bp = 0;
		}
		selUnit = -1;
		pathFinder->ResetMap();
	}
}

void Game::selectUnit(int sp, int su)
{
	int bp = 0;
	selUnit = su;
	pathFinder->DoUnitMaxDistanceTravel(players[curPlayer].GetUnit(selUnit),10);

}



bool Game::getCharacterAt(int cx, int cy, int& sPlayer, int& sUnit)
{
	int pnum = 0;
	int unum = 0;
	for (auto iplayer : players) {
		for (auto unit : iplayer.GetUnits()) {
			if ((unit.GetX() == cx) && (unit.GetY() == cy)) {
				sPlayer = pnum;
				sUnit = unum;
				return true;
			}
			unum++;
		}
		pnum++;
	}
	return false;
}

//This has to be static unless we want to pass 100K vars around.
//Each action, when it closes, adds an action.
void Game::addAction(Action* action, Action* ref)
{
	if (ref == nullptr) {
		gameInstance->actions.push_back(action);
	}/*
	else {
		for (int i = 0; i < gameInstance->actions.size(); i++) {
			if 
		}
		if (gameInstance->actions.find(ref) != gameInstance->end()) {
			//insert before 

		}
	}*/
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
	
	const uint8_t* ks = SDL_GetKeyboardState(NULL);
	if (ks[SDL_SCANCODE_W]) cy -= 0.001;
	if (ks[SDL_SCANCODE_S]) cy += 0.001;
	if (ks[SDL_SCANCODE_A]) cx -= 0.001;
	if (ks[SDL_SCANCODE_D]) cx += 0.001;
	
	handleMouse();
	
	viewPort.SetCamera(cx, cy);
	viewPort.Update(1);
	SDL_Rect myRect;

	Display::Clear(0, 0, 0);
	//Get the background up there.........
	SDL_Texture* tempTex = AssetMgr::GetAll("BKG", myRect);
	SDL_Rect screen = { 0,0,1600,800 };
	SDL_RenderSetClipRect(Display::GetRenderer(), &screen);
	Display::DrawTexture(tempTex, &myRect, &screen);
	//Ref out for mCell*
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
	
	GamePlayer player;
	players.push_back(player);
	curPlayer = 0;
	selUnit = -1; //No unit;
}

void Game::NextPlayer()
{
	curPlayer++;
	curPlayer = curPlayer % players.size();
}

/*private static members*/
Game* Game::gameInstance;

int Game::mCellX = 5;
int Game::mCellY = 5;
