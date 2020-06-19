#pragma once
#include "map.h"
#include "Unit.h"
#include "viewport.h"



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
	Map* gameMap;
	std::vector<Unit> units;

public:
	static Game* gameInstance;
	ViewPort viewPort;
	static void Create();
	static void ProcessEvents();
	void Process();
	void StartUp(int x, int y);


	static inline bool IsRunning() { return gameInstance->running; }
};