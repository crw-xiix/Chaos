/*
Author:
Charles Wood
7-2-2020
*/

#include "pch.h"
#include "font16.h"
#include "assetmgr.h"

//Note, couldn't figure out how to make it static, but whatever for now.
int spacing[97] { 1,1,8,16,29,40,54,66,71,79,86,94,105,110,118,123,131,142,150,160,170,181,192,203,212,223,234,240,246,257,268,279,289,304,314,325,336,347,357,366,377,388,395,402,414,423,436,447,458,468,479,490,500,510,521,532,548,558,568,577,585,594,601,612,624,631,641,651,661,671,681,688,698,708,714,720,730,736,750,760,770,780,790,798,808,815,825,835,848,857,867,874,883,889,898,908,908 };

void Font16::DrawText(const std::string &str, int x, int y)
{
	for (char c : str) {
		x += DrawLetter(c,x,y);
	}
}

int Font16::TextLength(const std::string &str, int at)
{
	int idx = 0;
	int x=0;
	for (char c : str) {
		
		int idx = (int)c - 32;
		if (idx == 0) {
			x += 4;
		}
		else {
			x += spacing[idx + 1] - spacing[idx];
		}
		at--;
		if (at == 0) break;
	}
	return x;
}

int Font16::DrawLetter(char c, int x, int y) {
	int idx = (int)c;
	if (idx < 32) return 0;
	if (idx > 127) return 0;
	idx -= 32;
	if (idx == 0) return 4;
	SDL_Rect texRect;
	//Below can be optimized
	SDL_Texture* fontText = AssetMgr::GetAll("FONT16", texRect);
	//Pick out our location in the buffer for the string
	texRect.x = spacing[idx];
	texRect.w = spacing[idx + 1] - spacing[idx];
	texRect.y = 0;
	texRect.h = 16;
	SDL_Rect ilocation{ x,y,texRect.w,texRect.h };
	Display::DrawTexture(fontText, &texRect, &ilocation);
	return texRect.w;
}