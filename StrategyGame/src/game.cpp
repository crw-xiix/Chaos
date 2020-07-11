#include "pch.h"
#include "pch.h"
#include "game.h"
#include "assetmgr.h"
#include "viewport.h"
#include "actionintro.h"
#include <functional>
#include "keymanager.h"

//XXXC CRW Need an action for requesting new room, joining room, etc.

Game::Game() : running(true), console{ nullptr }
{
	socketQueue = nullptr;
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
		} else { //Upclick
			int imx, imy;
			viewPort.GetCellAtMouseXY(mx, my, imx, imy);
			if ((imx == lastMouseCell.x) && (imy == lastMouseCell.y)) {
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
	if (actions.size() > 0) {
		actions[actions.size() - 1]->Click();
		return;
	}
	int sp, su;
	//Bail out, out of range click
	if ((lastMouseCell.x < 0) || (lastMouseCell.y < 0)) {
		return;
	}
	if ((lastMouseCell.x >=Map::Size) || (lastMouseCell.y >= Map::Size)) return;

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
				if (socketQueue) {
					socketQueue->Send(test);
				}
				auto thePath = pathFinder->GetPathTo(lastMouseCell.x, lastMouseCell.y);
				for (auto me : thePath) {
					addAction(new ActionMovePlayer(thisUnit, me.x, me.y));
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

void Game::keyPressed(int val)
{
}

void Game::SendMessage(std::string st)
{
	socketQueue->Send(st);
}

void Game::AddCallBack(std::function<bool(jute::jValue&)> callBack)
{
	callBacks = callBack;
}

void Game::RemoveCallBack()
{
	callBacks = nullptr;
}
void Game::SetRoomCode(const std::string& val)
{
	roomCode = val;
	console->AddLine("Joined Room:" + val);
}

void Game::onSelectServerCallback(std::string url)
{
	if (url == "QUIT") {
		running = false;
	}
	socketQueue = new SocketQueue(url);
	socketQueue->Start();
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

bool Game::keyDown(int val)
{
	if (keys.find(val) == keys.end()) {
		keys[val] = 0;
	}

	return keys[val] > 0;
}

void Game::HandleEvent(double ms) {
	// message processing loop
	SDL_Event event;
	int val;
	if (SDL_PollEvent(&event)) {

		switch (event.type) {

		case SDL_KEYDOWN:
			val = event.key.keysym.sym;
			if (keys.find(val) != keys.end()) {
				keys[val] = 0;
			}
			if (keys[val] == 0) {
				//This is where a key gets entered........
				const uint8_t* ks = SDL_GetKeyboardState(NULL);
				bool shift =
					((ks[SDL_SCANCODE_LSHIFT] > 0) || (ks[SDL_SCANCODE_RSHIFT]>0));
				KeyboardManager::KeyManager->AddKeyDown(val,shift);
			}
			keys[val] += ms;
			if (val == SDLK_BACKSPACE) {
				if (keys[val]> 0.50) ms = 0;
			}
			else {
				if (keys[val] > 0.25) ms = 0;
			}

			break;
		case SDL_KEYUP:
			if (keys[event.key.keysym.scancode == SDL_SCANCODE_LSHIFT]) {
			}

			val = event.key.keysym.sym;
			keys[val] = 0;
			break;
		case SDL_QUIT:
			{
				gameInstance->running = false;
			}
		default:
			break;
		}
	}
}
//static
void Game::ProcessEvents()
{
	Game::gameInstance->HandleEvent(0);
	
	if (gameInstance->socketQueue) {
		gameInstance->socketQueue->Process();

		//int sz = gameInstance->socketQueue->Avail();
		if (gameInstance->socketQueue->Avail()) {
			//The temp is for setting breakpoints
			std::string temp = gameInstance->socketQueue->Peek();
			gameInstance->console->AddLine(temp);

			//Also need to see if the current callback is ready for the message
			//If not, leave the message in there and wait till something else
			//Is up and running to accept the message.
			if (gameInstance->callBacks != nullptr) {
				//Call it..
				//This will happen a few time during transition, but it's okay for now.
				//Could cache it, or just store the Json in SocketCallBack
				jute::jValue json = jute::parser::parse(temp);
				if ((gameInstance->callBacks)(json)) {
					//Now we can remove it.
					gameInstance->socketQueue->Get();
				}
			}
			std::cout << temp << std::endl;
			int bp = 0;
		}
	}
}

bool Game::Process(double deltaTime) {
	bool doKeyb = true;

	//std::cout << "Frame time: " << deltaTime << "\n";
	if (actions.size() > 0) {
		//We need the last Action/Current Action iterator, so we can delete later.
		auto location = (actions.end() - 1);
		auto action = *location;
		if (action->HasKeyboardControl()) {
			doKeyb = false;
		}
	}
	
	if (doKeyb) {
		
		const uint8_t* ks = SDL_GetKeyboardState(NULL);
		if (ks[SDL_SCANCODE_W] > 0) cy -= 0.001;
		if (ks[SDL_SCANCODE_S] > 0) cy += 0.001;
		if (ks[SDL_SCANCODE_A] > 0) cx -= 0.001;
		if (ks[SDL_SCANCODE_D] > 0) {
			cx += 0.001;
		}
	}
	viewPort.SetCamera(cx, cy);
	viewPort.Update(deltaTime);
	size_t size = actions.size();

	if (size > 0) {
		//We need the last Action/Current Action iterator, so we can delete later.
		auto location = (actions.end() - 1);
		//Now we have the action...
		Action* action = *location;
		bool resultClose = action->Process(deltaTime);

		if (resultClose) {
			//We have to delete the current one before we can add the new one(s) on top...
			std::list<Action*> tempActions = action->GetNext();
			actions.erase(location);
			if (tempActions.size() != 0) {
				for (auto a : tempActions) {
					addAction(a);
				}
			}
			//Must do this last.
			delete action;
		}
	}
	handleMouse();
	Draw(deltaTime);
	return running;
}

void Game::Draw(double deltaTime)
{
	SDL_Rect myRect;

	//Get the background up there.........
	SDL_Texture* tempTex = AssetMgr::GetAll("BKG", myRect);
	SDL_Rect screen = { 0,0,1600,800 };
	SDL_RenderSetClipRect(Display::GetRenderer(), &screen);
	Display::DrawTexture(tempTex, &myRect, &screen);
	
	//Draw the map
	viewPort.Draw(*gameMap, players, pathFinder);

	SDL_RenderSetClipRect(Display::GetRenderer(), &screen);
	//Do actions, if they need to draw....

	size_t size = actions.size();
	if (size > 0) {
		//We need the last Action/Current Action iterator, so we can delete later.
		auto location = (actions.end() - 1);
		//Now we have the action...
		Action* action = *location;
		action->Draw();
	}

	//No mouse during action time for now

	console->Draw();
	//Draw the UI......
}

void Game::StartUp(int x, int y)
{
	gameMap = new Map();
	gameMap->Generate();

	pathFinder = new PathFinder(*gameMap);
		
	//These numbers come from the background image........
	viewPort = ViewPort(325, 75, 1225, 675, 1.0f);
	console = new ConsoleView(16, 464, 272, 320, 18);
	console->AddLine("Starting");
	GamePlayer player;
	players.push_back(player);
	curPlayer = 0;
	selUnit = -1; //No unit;
	
	//Get our time setup properly.....
	now = SDL_GetPerformanceCounter();
	addAction(new ActionIntro());
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

/*Static Members*/
Game* Game::gameInstance;

int Game::mCellX = 5;
int Game::mCellY = 5;
