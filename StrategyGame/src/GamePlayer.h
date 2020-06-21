#pragma once
#include "pch.h"
#include "Unit.h"

class GamePlayer {
private:
	std::vector<Unit> units;
	//temp
	static constexpr int initUnits = 4;

public:
	GamePlayer();

	const inline std::vector<Unit>& GetUnits() const { return units; }
};
