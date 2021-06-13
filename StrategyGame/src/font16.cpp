/*
Author:
Charles Wood
7-2-2020
*/

#include "pch.h"
#include "font16.h"
#include "assetmgr.h"

//Note, couldn't figure out how to make it static, but whatever for now.
int spacing16[97] { 1,1,8,16,29,40,54,66,71,79,86,94,105,110,118,123,131,142,150,160,170,181,192,203,212,223,234,240,246,257,268,279,289,304,314,325,336,347,357,366,377,388,395,402,414,423,436,447,458,468,479,490,500,510,521,532,548,558,568,577,585,594,601,612,624,631,641,651,661,671,681,688,698,708,714,720,730,736,750,760,770,780,790,798,808,815,825,835,848,857,867,874,883,889,898,908,908 };
int spacing32[97]{ 1,1,14,31,56,77,103,127,138,152,166,180,202,213,227,238,256,276,291,310,330,350,370,390,407,427,447,458,469,490,511,532,553,582,603,624,645,666,683,700,721,742,754,768,790,806,832,852,872,892,912,932,953,972,993,1014,1044,1064,1084,1101,1114,1132,1145,1165,1188,1201,1221,1242,1262,1283,1303,1317,1338,1359,1371,1383,1403,1415,1444,1465,1485,1506,1527,1543,1562,1577,1598,1618,1644,1663,1682,1698,1714,1725,1741,1762,1762 };
//Make a 64px later on.


void Font16::DrawText(const std::string& str, int x, int y)
{
	for (char c : str) {
		x += DrawLetter(c, x, y);
	}
}

int Font16::TextLength(const std::string& str, int at)
{
	int idx = 0;
	int x = 0;
	for (char c : str) {

		int idx = (int)c - 32;
		if (idx == 0) {
			x += 4;
		}
		else {
			x += spacing16[idx + 1] - spacing16[idx];
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
	texRect.x = spacing16[idx];
	texRect.w = spacing16[idx + 1] - spacing16[idx];
	texRect.y = 0;
	texRect.h = 16;
	SDL_Rect ilocation{ x,y,texRect.w,texRect.h };
	Display::DrawTexture(fontText, &texRect, &ilocation);
	return texRect.w;
}

int Font16::GetHeight()
{
	return 32;
}



void Font32::DrawText(const std::string& str, int x, int y)
{
	for (char c : str) {
		x += DrawLetter(c, x, y);
	}
}

int Font32::GetHeight()
{
	return 32;
}

int Font32::TextLength(const std::string& str, int at)
{
	int idx = 0;
	int x = 0;
	for (char c : str) {

		int idx = (int)c - 32;
		if (idx == 0) {
			x += 4;
		}
		else {
			x += spacing32[idx + 1] - spacing32[idx];
		}
		at--;
		if (at == 0) break;
	}
	return x;
}

int Font32::DrawLetter(char c, int x, int y) {
	int idx = (int)c;
	if (idx < 32) return 0;
	if (idx > 127) return 0;
	idx -= 32;
	if (idx == 0) return 4;
	SDL_Rect texRect;
	//Below can be optimized
	SDL_Texture* fontText = AssetMgr::GetAll("FONT32", texRect);
	//Pick out our location in the buffer for the string
	texRect.x = spacing32[idx];
	texRect.w = spacing32[idx + 1] - spacing32[idx];
	texRect.y = 0;
	texRect.h = 32;
	SDL_Rect ilocation{ x,y,texRect.w,texRect.h };
	Display::DrawTexture(fontText, &texRect, &ilocation);
	return texRect.w;
}