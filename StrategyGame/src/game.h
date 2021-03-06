#pragma once
#include "map.h"
#include "unit.h"
#include "viewport.h"
#include "pathfind.h"
#include "action.h"
#include "console.h"
#include "socketqueue.h"
#include "inputmanager.h"
#include <functional>
#include "../3rd/jute.h"
#include "playerstatus.h"

class Game
{
public:
	static int mCellX, mCellY;
	static Game* gameInstance;

	static void Create();
	static void Destroy();
	static void ProcessEvents();
	bool Process(double DeltaTime);
	void Draw(double deltaTime); 
	void StartUp(int x, int y);
	void NextPlayer();
	static inline bool IsRunning() { return gameInstance->running; }
	//To server
	void SendMessage(std::string st);


	void SetMsgCallBack(std::function<bool(jute::jValue&)> callBack);
	void RemoveCallBack();
	void SetRoomCode(const std::string& val);
	std::string GetRoomCode();
public: //static
	void onSelectServerCallback(std::string url);
private:
	bool handleLocal(jute::jValue& val);

private:
	double elapsedTime = 0;
	double lastPing = 0;
	std::string roomCode = "";
	std::function<bool(jute::jValue&)> msgCallBack;
	InputManager keyMan;
	
	std::map<int, double> keys;  //numbers to wild for array....
	bool keyDown(int val);
	void HandleEvent(double ms);
	
	
	/// <summary>
	/// This converts the pointer to a unique pointer and claims ownership.
	/// </summary>
	/// <param name="action"></param>
	/// <param name="ref"></param>
	static void addAction(Action* action);
	SocketQueue *socketQueue=nullptr;

	bool running= false;
	//Camera Location
	double cx = 0;
	double cy = 0;

	Game();
	~Game();

	//Stuff we need for game
	Map* gameMap = nullptr;
	std::vector<GamePlayer> players;
	ViewPort viewPort;
	ConsoleView* console = nullptr;
	PlayerStatus* playerStatus = nullptr;

	PathFinder* pathFinder = nullptr;

	int curPlayer = -1;
	int selUnit = -1;

	SDL_Point lastMouseCell{ -1,-1 };
	bool mouseDown = false;

	std::vector<std::unique_ptr<Action>> actions;
	Uint64 now = 0;
	Uint64 last = 0;
	void handleMouse();
	void click();
	void selectUnit(int sp, int su);
	//Gets the character at cell x,y (not mouse location)
	bool getCharacterAt(int cx, int cy, int& sPlayer, int& sUnit);
	void keyPressed(int val);
};
