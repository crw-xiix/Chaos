#pragma once
#include "map.h"
#include "unit.h"
#include "viewport.h"
#include "pathfind.h"
#include "action.h"
#include "console.h"
#include "socketqueue.h"

class Game
{
public:
	static int mCellX, mCellY;
	static Game* gameInstance;

	static void Create();
	static void ProcessEvents();
	void Process();
	void StartUp(int x, int y);
	void NextPlayer();
	static inline bool IsRunning() { return gameInstance->running; }
public: //static
	static void addAction(Action* action, Action* ref = nullptr);

private:
	SocketQueue *socketQueue=nullptr;

	bool running;
	//Camera Location
	double cx = 0;
	double cy = 0;

	Game();
	~Game();

	//Stuff we need for game
	Map* gameMap = nullptr;
	std::vector<GamePlayer> players;
	ViewPort viewPort;
	ConsoleView *console;

	PathFinder* pathFinder = nullptr;

	int curPlayer = -1;
	int selUnit = -1;

	SDL_Point lastMouseCell{ -1,-1 };
	bool mouseDown;
	std::vector<Action*> actions;
	Uint64 now;
	Uint64 last;
	void handleMouse();
	void click();
	void selectUnit(int sp, int su);
	//Gets the character at cell x,y (not mouse location)
	bool getCharacterAt(int cx, int cy, int& sPlayer, int& sUnit);
};
