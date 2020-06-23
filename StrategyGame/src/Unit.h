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
	//Speed is how many regular tiles it can travel per round/Tile slowness.
	int speed = 20;

	int constitution = 50;
	int range;
	float damage;

	int x;
	int y;

public:
	static constexpr int ConstMax = 50;
	Unit(UnitType type, int x, int y);

	void Draw(SDL_Rect dest);

	inline int GetX() const { return x; }
	inline int GetY() const { return y; }
	inline int GetSpeed() const { return speed; }
};