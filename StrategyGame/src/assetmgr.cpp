#pragma once
#include "pch.h"
#include "assetmgr.h"


void AssetMgr::Destroy()
{
	for (auto i : AssetMgr::Images) SDL_DestroyTexture(i.second);
}

bool AssetMgr::Load(std::string filename, std::string nick)
{
	SDL_Texture* texture = IMG_LoadTexture(Display::GetRenderer(), filename.c_str());
	Images[nick] = texture;
	return false;
}

SDL_Texture* AssetMgr::Get(std::string nick, int gridSize, int x, int y, SDL_Rect& dest) {
	SDL_Texture* tex = Images[nick];
	if (tex == nullptr) return tex;
	dest.x = gridSize * x;
	dest.y = gridSize * y;
	dest.w = gridSize;
	dest.h = gridSize;
	return tex;
}

SDL_Texture* AssetMgr::GetAll(std::string nick, SDL_Rect& dest)
{
	SDL_Texture* tex = Images[nick];
	Uint32 fmt;
	int acs;
	dest.x = 0;
	dest.y = 0;
	SDL_QueryTexture(tex, &fmt, &acs, &dest.w, &dest.h);
		
	return tex;
}


//Statics
std::map<std::string, SDL_Texture*> AssetMgr::Images;
