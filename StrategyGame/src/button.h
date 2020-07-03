/*
Author:
Charles Wood
7-2-2020
*/
#pragma once
#include "pch.h"
#include <functional>
#include "visualbase.h"

class Button : public VisBase {
public:
	Button(int x, int y, int w, int h);
	void SetText(std::string val);
	void SetTexture(SDL_Texture* tex);
	void SetOnClick(std::function<void(void)> func);
	void MouseIn() override;
	void MouseOut() override;
	void MouseDown() override;
	void MouseUp() override;
	void Draw() override;
	void MouseClick(int mx, int my) override;
protected:
	void DrawNumber(SDL_Rect location, char c);
	std::function<void(void)> onClick;
	SDL_Texture* texture=nullptr;
	std::string label{ "" };
};
