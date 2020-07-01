#pragma once
#include "pch.h"
#include "SDL.h"


class ConsoleView {
private:
	std::list<std::string> data;
	SDL_Rect window;
	int maxLines = 10;
public:
	ConsoleView(int x, int y, int w, int h, int lines);
	void AddLine(std::string text);
	void Clear();
	void DrawNumber(SDL_Rect location, char c);
	void Draw();
};

