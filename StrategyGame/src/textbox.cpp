#include "pch.h"
#include "textbox.h"
#include "display.h"
#include "font16.h" 

TextBox::TextBox(int x, int y, int w, int h) 
{
	font = std::make_unique<Font16>( Font16() );
	location = SDL_Rect{ x,y,w,h };
	canFocus = true;
}

void TextBox::SetFont(std::unique_ptr<FontFixed> val) { 
	font = std::move(val); 
};

void TextBox::SetEnabled(bool val) {
	enabled = val;
}


void TextBox::SetText(std::string val)
{
	label = val;
}

std::string TextBox::GetText()
{
	return label;
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
	if (canFocus) {
		hasFocus = true;
	}
}


void TextBox::MouseUp()
{
}

void TextBox::Draw()
{
	//Font16 ourFont;
	//we need a black box
	if (enabled) {
		SDL_SetRenderDrawColor(Display::GetRenderer(), 0, 0, 0, 255);
	}
	else {
		SDL_SetRenderDrawColor(Display::GetRenderer(), 63, 63, 63, 255);
	}

	SDL_RenderFillRect(Display::GetRenderer(), &location);

	//We need a border
	if (hasFocus) {
		SDL_SetRenderDrawColor(Display::GetRenderer(), 255, 255, 255, 255);
	}
	else {
		SDL_SetRenderDrawColor(Display::GetRenderer(), 127,127,127,255);
	}
	SDL_RenderDrawRect(Display::GetRenderer(), &location);

	font->DrawText(label,location.x + 2, location.y + 2);

	
	if (showCursor && hasFocus) {
		//Got figure out where the cursor is.....
		int curOffset = 0;
		if (cursorX > 0) {
			//std::string x = label.substr(0, curX);
			curOffset = font->TextLength(label,cursorX);
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
	if (!hasFocus) return;
	if (allowedChars.length() > 0) {
		if (allowedChars.find(key) <0) return;
	}

	if (key == SDLK_BACKSPACE) {
		if (cursorX > 0) {
			cursorX--;
			label.erase(label.begin() + cursorX);
		}
	}
	if (key == SDLK_DELETE) {
		try {
			label.erase(label.begin() + cursorX);
		} catch (...) {
		}
	}
	if (key == SDLK_LEFT) {
		if (cursorX > 0) {
			cursorX--;
		}
	}

	if (key == SDLK_END) {
		cursorX = (int)label.size();
	}
	if (key == SDLK_HOME) {
		cursorX = 0;
	}
	//Have to rearrange for those that add letters or move cursor
	if (!(cursorX < maxLen)) {
		//xxxc crw maybe beep here....
		return;
	}
	if (key == SDLK_RIGHT) {
		if (cursorX < (label.size() )) {
			cursorX++;
		}
	}
	if (label.length() >= maxLen) {
		//xxxc crw should beep here......
		return;
	}
	if ((key >= 32) && (key < 127)) {
		if (allCaps) key = static_cast<char>(std::toupper(key));
		label.insert(label.begin() + cursorX, (char)key);
		cursorX++;
	}

}
