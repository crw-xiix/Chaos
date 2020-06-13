#pragma once

class Game
{
private:
	static Game* gameInstance;
	bool running;

	Game();
	~Game();

public:
	static void Create();
	static void ProcessEvents();

	static inline bool IsRunning() { return gameInstance->running; }
};