#include "pch.h"
#include "pch.h"
#include "game.h"
#include "assetmgr.h"
#include "viewport.h"



/*
#include "websocketpp/config/asio_no_tls_client.hpp"
#include "websocketpp/client.hpp"
*/

//XXXC CRW Need an action for requestion new room, joining room, etc.

Game::Game()
	: running(true)
{
	socketQueue = new SocketQueue("ws://71.56.75.25:82/chat");
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
	//Bail out, out of range click
	if ((lastMouseCell.x < 0) || (lastMouseCell.y < 0)) return;
	if ((lastMouseCell.x >=Map::Size) || (lastMouseCell.y > Map::Size)) return;

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
		if (selUnit != -1) {
			if (pathFinder->GetRange(lastMouseCell.x, lastMouseCell.y) > -1) {
				//This should be a valid move.

				auto& thisUnit = players[curPlayer].GetUnit(selUnit);
				std::string msg = "Move to:";
				msg += std::to_string(lastMouseCell.x) + " ";
				msg += std::to_string(lastMouseCell.y) + " ";
				std::string test = "{\"request\":\"create\"}";
				//console->AddLine(msg);
				console->AddLine(msg);
				socketQueue->Send(test);
				auto thePath = pathFinder->GetPathTo(lastMouseCell.x, lastMouseCell.y);
				for (auto me : thePath) {
					addAction(new ActionMovePlayer(thisUnit, me.x, me.y));
					/*actions.insert(actions.begin(), ActionMovePlayer(thisUnit, me.x, me.y));
					actions.insert()*/
				}
				//thisUnit.Move(lastMouseCell.x, lastMouseCell.y);
				int bp = 0;
			}
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

	gameInstance->socketQueue->Process();
	//int sz = gameInstance->socketQueue->Avail();
	if (gameInstance->socketQueue->Avail()) {
		//The temp is for setting breakpoints
		std::string temp = gameInstance->socketQueue->Get();
		gameInstance->console->AddLine(temp);
		std::cout << temp << std::endl;
		int bp = 0;
	}

}

void Game::Process() {
	last = now;
	now = SDL_GetPerformanceCounter();

	double deltaTime = (double)((now- last)  / (double)SDL_GetPerformanceFrequency());
	//std::cout << "Frame time: " << deltaTime << "\n";
	const uint8_t* ks = SDL_GetKeyboardState(NULL);
	if (ks[SDL_SCANCODE_W]) cy -= 0.001;
	if (ks[SDL_SCANCODE_S]) cy += 0.001;
	if (ks[SDL_SCANCODE_A]) cx -= 0.001;
	if (ks[SDL_SCANCODE_D]) cx += 0.001;

	size_t size = actions.size();
	if (size > 0) {
		if (actions[size - 1]->Process(deltaTime)) {
			delete actions[size - 1];
			actions.pop_back();
		}
	}
	else {
		//No mouse during action time for now
		handleMouse();
	}
	viewPort.SetCamera(cx, cy);
	viewPort.Update(1);
	SDL_Rect myRect;

	//Don't need to clear anything now
		//Display::Clear(0, 0, 0);
	//Get the background up there.........
	SDL_Texture* tempTex = AssetMgr::GetAll("BKG", myRect);
	SDL_Rect screen = { 0,0,1600,800 };
	SDL_RenderSetClipRect(Display::GetRenderer(), &screen);
	Display::DrawTexture(tempTex, &myRect, &screen);
	//Ref out for mCell*
	//Draw the map
	viewPort.Draw(*gameMap, players, pathFinder);
	SDL_RenderSetClipRect(Display::GetRenderer(), &screen);
	console->Draw();
	//Draw the UI......
}

void Game::StartUp(int x, int y)
{
	gameMap = new Map();
	gameMap->Generate();

	pathFinder = new PathFinder(*gameMap);

	AssetMgr::Load("assets/landscape.png", "LAND");
	AssetMgr::Load("assets/background.png", "BKG");
	AssetMgr::Load("assets/Dudes.png", "UNITS");
	AssetMgr::Load("assets/highlights.png", "HIGHLIGHT");
	AssetMgr::Load("assets/font16.png", "FONT16");
		
	//These numbers come from the background image........
	viewPort = ViewPort(325, 75, 1225, 675, 1.0f);

	console = new ConsoleView(16, 464, 272, 320, 18);
	console->AddLine("Starting");
	console->AddLine("testing 1234567890123456789012345678901234");
	GamePlayer player;
	players.push_back(player);
	curPlayer = 0;
	selUnit = -1; //No unit;
	socketQueue->Start();
}

void Game::NextPlayer()
{
	curPlayer++;
	curPlayer = curPlayer % players.size();
}

Game::~Game()
{
	delete socketQueue;
	delete console;
	delete gameInstance;
	
}



/*private static members*/
Game* Game::gameInstance;

int Game::mCellX = 5;
int Game::mCellY = 5;
