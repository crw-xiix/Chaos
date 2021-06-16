#include "pch.h"
#include "game.h"
#include "assetmgr.h"
#include "viewport.h"
#include "actionintro.h"
#include <functional>
#include "keymanager.h"



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
		(actions[actions.size() - 1])->Click();
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
				for (auto &me : thePath) {
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
	for (auto &iplayer : players) {
		for (auto &unit : iplayer.GetUnits()) {
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

//void Game::SetMsgCallBack(std::function<bool(jute::jValue&)> callBack)
void Game::SetMsgCallBack(std::function<bool(jute::jValue&)> callBack)
{
	msgCallBack = callBack;
}

void Game::RemoveCallBack()
{
	msgCallBack = nullptr;
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
void Game::addAction(Action* action)
{
	gameInstance->actions.emplace_back(std::unique_ptr<Action>(action));
}

//static
void Game::Create()
{
	gameInstance = new Game();
}

void Game::Destroy()
{
	delete gameInstance;
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
				break;
			}
		default:
			break;
		}
	}
}


bool Game::handleLocal(jute::jValue& v)
{
	//This just clears out stuff that isn't for the actions/menus....
	std::string resp = v["request"].as_string();
	if (resp == "userid") {
		gameInstance->console->AddLine("User Id recvd");
		return true;
	}
	if (resp == "ping") {
		gameInstance->console->AddLine("Pinged");
		lastPing = elapsedTime;
		return true;
	}
	//This will help in debugging
	if (resp == "error") {
		std::string msg = v["message"].as_string();
		gameInstance->console->AddLine(msg);
		return true;
	}
	return false;
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
			//gameInstance->console->AddLine(temp);
			
			//This will happen a few time during transition, but it's okay for now.
			//Could cache it, or just store the Json in SocketCallBack
			jute::jValue json = jute::parser::parse(temp);
			if (gameInstance->handleLocal(json)) {
				//Remove it
				gameInstance->socketQueue->Get();
				return;
			}
			//Also need to see if the current callback is ready for the message
			//If not, leave the message in there and wait till something else
			//Is up and running to accept the message.

			try {
				if (gameInstance->msgCallBack != nullptr) {

					if ((gameInstance->msgCallBack)(json)) {
						//Now we can remove it.
						gameInstance->socketQueue->Get();
					}
				}
			}
			catch (...) {
			
			}
			std::cout << temp << std::endl;
			int bp = 0;
		}
	}
}
/*

#include <array>
#include <list>
#include <string>
#include <vector>

#include <iostream>
#include <sstream>
#include <fstream>

#include <functional>
#include <memory>
#include <map>


using namespace std;

class Employee {
public:
	Employee(string iname = "") { name = iname; }
	string name = "No Name";
	bool onVacation = true;
	virtual void display() {
		cout << "    Name: " << name << "\nVacation: " << (onVacation ? "Yes" : "No") << "\n\n";
	}
	virtual ~Employee() {
		cout << "Employee::Dtor::" << name << "\n";
	}
};

class Manager : public Employee {
public:
	Manager(string iname = "") : Employee(iname) {

	}
	virtual void display() {
		cout << "------------Manager--------------\n";
		Employee::display();
	}
	~Manager() {
		cout << "Manager::Employee::Dtor::" << name << "\n";
	}

};

void whyNot(Employee* toAdd) {
	std::vector< std::unique_ptr<Employee> > objs;

	objs.emplace_back(unique_ptr<Employee>(toAdd));
	cout << "\n\nWhy not:--------------------------------------------------- \n\n";
	for (auto const& p : objs) {
		p->display();
	}
}

int main()
{
	// Create an Employee on the stack
	// Employee EmpRec("Cliff");

	 //EmpRec.onVacation = true; 
	Employee* test = new Employee("Chuck");  //dtor
	Employee* man = new Manager("The Man");  //dtor 2x

	// Assign values to a uniqueptrs

	//This is normal way
	unique_ptr<Employee> tempEmp(new Employee("Justin")); //dtor
	//This is odd.
	unique_ptr<Employee> tempEmp2(test);

	//This is inheritance check;
	unique_ptr<Employee> tempEmp3 = std::make_unique<Employee>("Stock Worker 2");//dtor
	unique_ptr<Employee> tempEmp4(man);

	// *tempEmp = std::move(EmpRec); //this is a copy......
	*tempEmp2 = std::move(*test);
	// *tempEmp = std::move( &EmpRec);

	//tempEmp.get()->name = "Tyreke";

	tempEmp.get()->display();
	tempEmp2.get()->display();
	tempEmp3.get()->display();
	tempEmp4.get()->display();



	Employee* man2 = new Manager("The Man #2");  //dtord
	man2->onVacation = false;

	Employee* man3 = new Manager("CEO");
	//Okay now to arrays/vecs

	cout << "PolyMorphic vector of Employees\n";
	std::vector< std::unique_ptr<Employee> > objs;

	objs.emplace_back(unique_ptr<Employee>(man2));
	objs.emplace_back(unique_ptr<Employee>(man3));
	objs.emplace_back(unique_ptr<Employee>(new Employee("Jill"))); //jill dtor
	//managers
	cout << "Managers: \n";
	for (auto const& p : objs) {
		p->display();
	}
	man->onVacation = false;
	whyNot(man3);
	//objs.emplace_back(tempEmp);

}
*/

bool Game::Process(double deltaTime) {
	bool doKeyb = true;
	elapsedTime = deltaTime;

	if (actions.size() > 0) {
		//This just allows some windows to let control keys through to gameInstance.
		if (doKeyb) {
			const uint8_t* ks = SDL_GetKeyboardState(NULL);
			if (ks[SDL_SCANCODE_W] > 0) cy -= 0.001;
			if (ks[SDL_SCANCODE_S] > 0) cy += 0.001;
			if (ks[SDL_SCANCODE_A] > 0) cx -= 0.001;
			if (ks[SDL_SCANCODE_D] > 0) {
				cx += 0.001;
			}
		}
		
	}
	
	viewPort.SetCamera(cx, cy);
	viewPort.Update(deltaTime);
	size_t size = actions.size();

	if (size > 0) {
		//We need the last Action/Current Action iterator, so we can delete later.
		auto location = (actions.end()-1);
		//Now we have the action...
		auto &action = actions.back();
		//Process can cause a message queue close, but it's usually the messageIn
		bool resultClose = action->Process(deltaTime);

		if (resultClose) {
			//We have to delete the current one before we can add the new one(s) on top...
			//We are only doing one action for now....
			Action* nextAction = action->GetNext();
			//Remove from container
			actions.pop_back();
			if (nextAction != nullptr) {
				addAction(nextAction);
			}
			//Must do this last.
		}
	}
	handleMouse();
	//Draw(deltaTime);
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
//		Action* action = *location;
		actions.back()->Draw();
	}

	//No mouse during action time for now
	console->Draw();
	//Draw the UI......
	playerStatus->Draw(players[0]);

	//
	
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
	playerStatus = new PlayerStatus(16, 51, 272, 400);
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
	delete playerStatus;
	delete gameInstance;
	
}

/*Static Members*/
Game* Game::gameInstance = nullptr;

int Game::mCellX = 5;
int Game::mCellY = 5;
