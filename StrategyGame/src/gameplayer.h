#pragma once
#include "pch.h"
#include "unit.h"

class GamePlayer {
private:
	std::vector<Unit> units;
	//temp
	static constexpr int initUnits = 1;

public:
	GamePlayer();

	const inline std::vector<Unit>& GetUnits() const { return units; }
	const inline Unit& GetUnit(int idx) { return GetUnits().at(idx); }
};
