#include "pch.h"
#include "Unit.h"
#include "Map.h"
#include "Display.h"
#include "AssetMgr.h"

Unit::Unit(UnitType type, int x, int y)
{
	this->type = type;

	this->x = x;
	this->y = y;

	texture = AssetMgr::Get("UNITS", Map::TileSize, 0, (int)type, rect);

	weapon = WeaponType::None;
	hp = 0.0f;
	speed = 0;
	range = 0;
	damage = 0.0f;

	//Weapon type and stats depend on unit type.
	switch (type)
	{
	case UnitType::Warrior:
		weapon = WeaponType::Melee;
		hp = 100.0f;
		speed = 4;
		range = 1;
		damage = 20.0f;
		break;

	case UnitType::Spear:
		weapon = WeaponType::Melee;
		hp = 100.0f;
		speed = 2;
		range = 1;
		damage = 35.0f;
		break;

	case UnitType::Archer:
		weapon = WeaponType::Ranged;
		hp = 75.0f;
		speed = 2;
		range = 5;
		damage = 20.0f;
		break;

	case UnitType::Wizard:
		weapon = WeaponType::Magic;
		hp = 50.0f;
		speed = 2;
		range = 2;
		damage = 40.0f;
		break;
	}
}

void Unit::Draw(SDL_Rect dest)
{
	Display::DrawTexture(texture, &rect, &dest);
}