#pragma once
#include "pch.h"
#include <string>

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

	int hp = 50;
	//Speed is how many regular tiles it can travel per round/Tile slowness.
	int speed = 20;

	int stamina = 50;
	int range;
	float damage;

	float x=1;
	float y=2;
	int frameNo=0;
	int frameDir = 1;
	int maxFrames = 1;

	int slowDown = 0;
public:
	int StaminaMax = 50;
	int HealthMax = 50;
	Unit(UnitType type, int x, int y);
	std::string GetJson();
	void Draw(SDL_Rect dest);

	inline int GetX() const { return (int) (x+.5f); }
	inline int GetY() const { return (int) (y+.5f); }
	//These return the float positions.
	inline float GetXF() const { return x; }
	inline float GetYF() const { return y; }

	inline int GetSpeed() const { return speed; }
	inline void Move(int dx, int dy) {
		x = (float) dx; y = (float) dy;
	}
	//This is for animations, to partial move the character.
	inline void MoveF(float dx, float dy) {
		x = dx; y = dy;
	}

};