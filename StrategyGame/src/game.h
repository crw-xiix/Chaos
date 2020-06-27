#pragma once
#include "map.h"
#include "unit.h"
#include "viewport.h"
#include "pathfind.h"


class Game
{
private:
	
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

	PathFinder* pathFinder;

	
public:
	static int mCellX, mCellY;
	static Game* gameInstance;
	
	static void Create();
	static void ProcessEvents();
	void Process();
	void StartUp(int x, int y);


	static inline bool IsRunning() { return gameInstance->running; }
};
