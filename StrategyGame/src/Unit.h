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

	int x;
	int y;

public:
	Unit(UnitType type, int x, int y);

	void Draw(SDL_Rect dest);

	inline int GetX() const { return x; }
	inline int GetY() const { return y; }
};