#include "pch.h"
#include "gameplayer.h"

GamePlayer::GamePlayer()
{
	for (int i = 0; i < initUnits; i++)
	{
		units.push_back(Unit(((UnitType)i), 10 + rand() % 12, 5 + rand() % 12));
	}
}

std::string GamePlayer::GetJson() {
	std::string result = "{";
	for (int i = 0; i < initUnits; i++)
	{
		result += units[i].GetJson();
		if (i < (initUnits - 1)) result += ",";
		result += "\n";
	}
	result += "}\n";
	return result;
}