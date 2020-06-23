#include "pch.h"
#include "GamePlayer.h"

GamePlayer::GamePlayer()
{
	for (int i = 0; i < initUnits; i++)
	{
		units.push_back(Unit(((UnitType)i), 10 + rand() % 12, 5 + rand() % 12));
	}
}