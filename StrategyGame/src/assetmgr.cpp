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
	if (texture == nullptr) {
		std::cout << "Failed to load:" << filename << "\n";
	}
	Images[nick] = texture;
	return false;
}

SDL_Texture* AssetMgr::Get(std::string nick, int gridSizeX, int gridSizeY, int x, int y, SDL_Rect& dest) {
	SDL_Texture* tex = Images[nick];
	if (tex == nullptr) return tex;
	dest.x = gridSizeX * x;
	dest.y = gridSizeY * y;
	dest.w = gridSizeX;
	dest.h = gridSizeY;
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
/// <summary>
/// Does not allocate memory...
/// </summary>
/// <param name="nick">Nick name of texture</param>
/// <returns>SDL_Texture by nick ame</returns>
SDL_Texture* AssetMgr::GetAll(std::string nick)
{
	SDL_Texture* tex = Images[nick];
	/*Uint32 fmt;
	int acs;
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	SDL_QueryTexture(tex, &fmt, &acs, &dest.w, &dest.h);*/
	return tex;
}


//Statics
std::map<std::string, SDL_Texture*> AssetMgr::Images;
