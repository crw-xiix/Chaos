/*
Author:
Charles Wood
7-2-2020
*/
#pragma once
#include "pch.h"
#include <functional>
#include "visualbase.h"

class Button : public VisualBase {
public:
	Button(int x, int y, int w, int h);
	void SetText(std::string val);
	void SetTexture(SDL_Texture* tex);
	void SetOnClick(std::function<void(void)> func);
	void MouseIn() override;
	void MouseOut() override;
	void MouseDown(int mx, int my) override;
	void MouseUp() override;
	void Draw() override;
	void MouseClick(int mx, int my) override;
	void Process(double ms) override;
protected:
	std::function<void(void)> onClick;
	SDL_Texture* texture=nullptr;
	std::string label{ "" };
};
