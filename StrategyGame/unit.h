#pragma once
#include"pch.h"

enum Unit_Type
{
	Cavalry = 0,
	Melee   = 1,
	Ranged  = 2,
	Wizard	= 3,
	Worker  = 4,
};
class Unit {

private:
	
	int x, y;
	float hp;
	float strength;
	float speed;
	Unit_Type type;


public:
	void Attack(Unit selected);
	void Attack(int x, int y);
	void Move(int x, int y);
	void Spawn(int x,int y);
};
/*had to go but im pushing all changes */