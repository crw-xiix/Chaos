#include "pch.h"
#include "textbox.h"
#include "display.h"
#include "font16.h" 

TextBox::TextBox(int x, int y, int w, int h)
{
	location = SDL_Rect{ x,y,w,h };
}

void TextBox::SetText(std::string val)
{
	label = val;
}

std::string TextBox::GetText()
{
	return std::string();
}

void TextBox::SetTexture(SDL_Texture* tex)
{
}

void TextBox::SetOnClick(std::function<void(void)> func)
{
}

void TextBox::MouseIn()
{
}

void TextBox::MouseOut()
{
}

void TextBox::MouseDown(int mx, int my)
{
}


void TextBox::MouseUp()
{
}

void TextBox::Draw()
{
	//we need a black box
	SDL_SetRenderDrawColor(Display::GetRenderer(), 0, 0, 0, 255);
	SDL_RenderFillRect(Display::GetRenderer(), &location);

	//We need a border
	SDL_SetRenderDrawColor(Display::GetRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawRect(Display::GetRenderer(), &location);

	Font16::DrawText(label,location.x + 2, location.y + 2);

	
	if (showCursor) {
		//Got figure out where the cursor is.....
		int curOffset = 0;
		if (curX > 0) {
			//std::string x = label.substr(0, curX);
			curOffset = Font16::TextLength(label,curX);
		}
		SDL_Rect cursor{ location.x + 2 + curOffset, location.y + 2, 1, location.h - 4 };
		SDL_RenderDrawRect(Display::GetRenderer(), &cursor);
	}

	std::map<char, int> vals;
	if (vals.find('c') != vals.end()) {}
	
}

void TextBox::MouseClick(int mx, int my)
{
}

void TextBox::Process(double ms)
{
	curTime += ms;
	if (curTime > 0.25) {
		curTime = 0;
		showCursor = !showCursor;
	}
}

void TextBox::KeyIn(int key)
{
	//so cursor is at zero.....
	//therefore insert at zero, then increment the cursor
	if ((key >= 32) && (key < 127)) {
		label.insert(label.begin() + curX, (char)key);
		curX++;
	}
	if (key == SDLK_BACKSPACE) {
		if (curX > 0) {
			curX--;
			label.erase(label.begin() + curX);
		}
	}
	if (key == SDLK_DELETE) {
		try {
			label.erase(label.begin() + curX);
		} catch (...) {
		}
	}
	if (key == SDLK_LEFT) {
		if (curX > 0) {
			curX--;
		}
	}
	if (key == SDLK_RIGHT) {
		if (curX < (label.size() )) {
			curX++;
		}
	}
	if (key == SDLK_END) {
		curX = label.size();
	}
	if (key == SDLK_HOME) {
		curX = 0;
	}
}
