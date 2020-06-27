#pragma once
#include "pch.h"
#include "unit.h"

class GamePlayer {
private:
	std::vector<Unit> units;
	//temp
	static constexpr int initUnits = 4;

public:
	GamePlayer();
	inline std::vector<Unit>& GetUnits()  { return units; }
	inline Unit& GetUnit(int idx) { return units[idx]; }
};
