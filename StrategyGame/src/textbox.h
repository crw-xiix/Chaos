#pragma once
#include "pch.h"
#include "visualbase.h"

class TextBox : public VisBase {
public:
	TextBox(int x, int y, int w, int h);
	void SetText(std::string val);
	std::string GetText();
	void SetTexture(SDL_Texture* tex);
	void SetOnClick(std::function<void(void)> func);
	void MouseIn() override;
	void MouseOut() override;
	void MouseDown(int mx, int my) override;
	void MouseUp() override;
	void Draw() override;
	void MouseClick(int mx, int my) override;
	void Process(double ms) override;
	void KeyIn(int key);
protected:
	double curTime = 0;
	bool showCursor{ false };
	int curX = 0;
	std::function<void(void)> onClick;
	SDL_Texture* texture = nullptr;
	std::string label{ "" };
};

