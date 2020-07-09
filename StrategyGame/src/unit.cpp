#include "pch.h"
#include "unit.h"
#include "map.h"
#include "display.h"
#include "assetmgr.h"

Unit::Unit(UnitType type, int x, int y)
{
	this->type = type;

	this->x = (float) x;
	this->y = (float) y;

	texture = AssetMgr::Get("UNITS", Map::TileSize, Map::TileSize, 0, (int)type, rect);

	weapon = WeaponType::None;
	hp = 0;
	speed = 0;
	range = 0;
	damage = 0.0f;

	//Weapon type and stats depend on unit type.
	switch (type)
	{
	case UnitType::Warrior:
		weapon = WeaponType::Melee;
		hp = 100;
		speed = 12;
		range = 1;
		damage = 20.0f;
		break;

	case UnitType::Spear:
		weapon = WeaponType::Melee;
		hp = 100;
		speed = 24;
		range = 1;
		damage = 35.0f;
		break;

	case UnitType::Archer:
		weapon = WeaponType::Ranged;
		hp = 100;
		speed = 30;
		range = 5;
		damage = 20.0f;
		break;

	case UnitType::Wizard:
		weapon = WeaponType::Magic;
		hp = 100;
		speed = 20;
		range = 2;
		damage = 40.0f;
		break;
	}
}

std::string jsonify(std::string key, std::string value) {
	std::string result = "";
	result += " \""+key+"\": \"";
	result += value + "\"";
	return result;
}

std::string Unit::GetJson()
{
	std::string result = "{\r\n";
	result += jsonify("hp", std::to_string(hp));
	result += ",\r\n";
	result += jsonify("x", std::to_string(GetX()));
	result += ",\r\n";
	result += jsonify("y", std::to_string(GetY()));
	result += "\r\n";
	result += "}\r\n";
	return result;
}

void Unit::Draw(SDL_Rect dest)
{
	Display::DrawTexture(texture, &rect, &dest);
}
