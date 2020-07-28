#include "pch.h"
#include "unit.h"
#include "map.h"
#include "display.h"
#include "assetmgr.h"
#include "json.h"


Unit::Unit(UnitType type, int x, int y)
{
	this->type = type;

	this->x = (float) x;
	this->y = (float) y;

	//texture = AssetMgr::Get("UNITS", Map::TileSize, Map::TileSize, 0, (int)type, rect);
	
	weapon = WeaponType::None;
	hp = 0;
	speed = 0;
	range = 0;
	damage = 0.0f;

	//Weapon type and stats depend on unit type.
	switch (type)
	{
	case UnitType::Warrior:
		maxFrames = 4;
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


std::string Unit::GetJson()
{
	std::string result = "{\r\n";
	result += Json::Jsonify("hp", hp);
	result += ",\r\n";
	result += Json::Jsonify("x", GetX());
	result += ",\r\n";
	result += Json::Jsonify("y", GetY());
	result += "\r\n";
	result += "}\r\n";
	return result;
}

void Unit::Draw(SDL_Rect dest)
{
	this->type = type;

	this->x = (float)x;
	this->y = (float)y;
	
	texture = AssetMgr::Get("UNITS", Map::TileSize, Map::TileSize, frameNo, (int)type, rect);
	slowDown++;
	if (slowDown == 60) {
		frameNo+=frameDir;
		slowDown = 0;
		if (frameNo >= maxFrames) {
			frameDir *= -1;
			frameNo += frameDir;
		}
		if (frameNo < 0) {
			frameDir *= -1;
			frameNo += frameDir;
		}


	}

	if (maxFrames > 1) {
			int breakPoint = 0;
	
	}

	if (frameNo > 1) {
		int breakpoint = 0;
	}
	if (maxFrames > 1) {
		int breakpoint=0;
		
	}
	
	


	Display::DrawTexture(texture, &rect, &dest);
}
