#pragma once
#include "pch.h"

enum class UnitType {
	Warrior = 0,
	Spear,
	Archer,
	Wizard,
};

enum class WeaponType
{
	None = 0,
	Melee,
	Ranged,
	Magic
};

class Unit {
private:
	UnitType type;
	WeaponType weapon;
	SDL_Rect rect;
	SDL_Texture* texture;

	float hp;
	int speed;
	int range;
	float damage;

public:
	Unit(UnitType type);
	
	void Draw(SDL_Rect dest);
};