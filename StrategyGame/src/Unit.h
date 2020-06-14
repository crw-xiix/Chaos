#include "pch.h"


enum Unit_Type {
	Melee,
	Spear,
	Range,
	Wizard,
	Worker
};


class Unit {
private:
	int x, y;
	float hp = 0.0f;
	float strength = 0.0f;
	float speed = 0.0f;
	Unit_Type unitType;
public:
	void Attack(Unit selected);
	void Attack(int x, int y);
	void Move(int x, int y);
	void Spawn(int x, int y);
};




