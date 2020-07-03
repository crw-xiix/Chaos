#pragma once
#include "pch.h"
#include <functional>

class VisBase {
public:
	virtual void MouseIn() = 0;
	virtual void MouseOut() = 0;
	virtual void MouseDown() = 0;
	virtual void MouseUp() = 0;
	virtual void MouseClick(int mx, int my) = 0;
	virtual void Draw() = 0;
protected:
	friend class MouseManager;
	SDL_Rect location{ 0 };
	bool hover = false;
	bool down = false;
};

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
	void DrawNumber(SDL_Rect location, char c);
	void Draw() override;
	void MouseClick(int mx, int my) override;
protected:
	std::function<void(void)> onClick;
	SDL_Texture* texture;
	std::string label;
};
