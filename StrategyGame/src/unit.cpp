#include"unit.h"

Unit::Unit() {
	x = 10;
	y = 43;
	hp = 10;
	strength = 5;
	speed = 2;
	type = Melee;
}


void Unit::Attack(Unit selected)
{
	Unit Knight = new Unit();
}

void Unit::Attack(int x, int y)
{
}

void Unit::Move(int x, int y)
{
	this->x = x;
	this->y = y;
	
}

void Unit::Spawn(int x, int y)
{
	
	Move(x, y);
}
