#include "pch.h"
#include "GamePlayer.h"

GamePlayer::GamePlayer()
{
	for (int i = 0; i < initUnits; i++)
	//for (int i = 0; i < 1; i++)

	{
		//units.push_back(Unit(((UnitType)i), 10, 10));
		units.push_back(Unit(((UnitType)i), 10 + rand() % 15, 10 + rand() % 15));
	}
}