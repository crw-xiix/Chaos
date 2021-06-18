#include "pch.h"
#include "label.h"
#include "font16.h"

Label::Label(int x, int y, int w, int h)
{
	location = SDL_Rect{ x,y,w,h };
}
Label::Label(SDL_Rect pos) {
	location = pos;
}

void Label::SetText(std::string val)
{
	label = val;
}

void Label::SetTexture(SDL_Texture* tex)
{
	//nothing, unless we want a background......
}

void Label::SetOnClick(std::function<void(void)> func)
{
	//we don't do this.
}

void Label::MouseIn()
{
}

void Label::MouseOut()
{
}

void Label::MouseDown(int mx, int my)
{
}

void Label::MouseUp()
{
}

void Label::Draw()
{
	Font16 ourFont;
	//center our location, and just draw it.....
	int labelL = ourFont.TextLength(label);
	int xs = (location.w - labelL) >> 1;
	int ys = (location.h - 16) >> 1;
	xs += location.x;
	ys += location.y;
	ourFont.DrawText(label, xs, ys);
}

void Label::MouseClick(int mx, int my)
{
}

void Label::Process(double ms)
{
}
