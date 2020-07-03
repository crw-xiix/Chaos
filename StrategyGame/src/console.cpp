#include "pch.h"
#include "console.h"
#include "assetmgr.h"

ConsoleView::ConsoleView(int x, int y, int w, int h, int lines)
{
	window = SDL_Rect{ x, y, w, h };
	maxLines = lines;
}

void ConsoleView::AddLine(std::string text)
{
	data.push_back(text);
	if (data.size() > maxLines) {
		data.pop_front();
	}
}

void ConsoleView::Clear()
{
	data.clear();
}

void ConsoleView::DrawNumber(SDL_Rect location, char c)
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
	SDL_Texture* fontText = AssetMgr::Get("FONT16", 16,16, idx, 0, texRect);
	Display::DrawTexture(fontText, &texRect, &location);
	
}
void ConsoleView::Draw()
{
	SDL_ClipRectSection myClip(window.x, window.y, window.w, window.h);
	//Change 16 to font size later on.
	SDL_Rect topLeft = SDL_Rect{ window.x,window.y, 16,16 };
	for (auto str : data) {
		for (char c : str) {
			DrawNumber(topLeft, c );
			topLeft.x += 16;
		}
		topLeft.x = window.x;
		topLeft.y += 16;
	}
}
