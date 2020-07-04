/*
Author:
Charles Wood
7-2-2020
*/

#include "pch.h"
#include "button.h"
#include "display.h"
#include "assetmgr.h"
#include "font16.h"

Button::Button(int x, int y, int w, int h)
{
	location = SDL_Rect{ x,y,w,h };
}

void Button::SetText(std::string val)
{
	label = val;
}

void Button::SetTexture(SDL_Texture* tex)
{
	texture = tex;
}

void Button::SetOnClick(std::function<void(void)> func)
{
	onClick = func;
}

void Button::MouseIn()
{
	hover = true;
}

void Button::MouseOut()
{
	hover = false;
}

void Button::MouseDown(int mx, int my)
{
	down = true;
}

void Button::MouseUp()
{
	down = false;
}

void Button::DrawNumber(SDL_Rect ilocation, char c)
{
	c = toupper(c);
	int idx = -1;

	if (c >= '0' && c <= '9') {
		idx = (int)c - '0';
	}
	if (c >= 'A' && c <= 'Z') {
		idx = ((int)(c - 'A')) + 10;
	}
	if (idx == -1) return;
	SDL_Rect texRect;
	SDL_Texture* fontText = AssetMgr::Get("FONT16",16,16,idx, 0,texRect);
	Display::DrawTexture(fontText,   &texRect, &ilocation);
}


void Button::Draw()
{
	SDL_Rect source{ 0, 0, location.w, location.h };
	if (hover) {
		source.y = 48;
	}
	if (down) source.y = 96;
	Display::DrawTexture(texture, &source, &location);
	//Change 16 to font size later on.
	SDL_Rect topLeft = SDL_Rect{ location.x,location.y, 16,16 };
	int xs, ys;
	int labelL = Font16::TextLength(label);

	xs = (location.w - labelL) >> 1;
	ys = (location.h - 16) >> 1;
	topLeft.x += xs;
	topLeft.y += ys;
	Font16::DrawText(label, topLeft.x, topLeft.y);
}

void Button::MouseClick(int mx, int my)
{
	onClick();
}

void Button::Process(double ms)
{
}
