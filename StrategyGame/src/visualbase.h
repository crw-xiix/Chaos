#pragma once
#include "pch.h"
#include <functional>

class VisualBase {
public:
	virtual void MouseIn() = 0;
	virtual void MouseOut() = 0;
	virtual void MouseDown(int mx, int my) = 0;
	virtual void MouseUp() = 0;
	virtual void MouseClick(int mx, int my) = 0;
	virtual void Draw() = 0;
	virtual void Process(double ms) = 0;
	virtual inline void KeyIn(int val) {};
protected:
	friend class InputManager;
	SDL_Rect location{ 0 };
	bool hover = false;
	bool down = false;
	bool canFocus = false;
	bool hasFocus = false;
};
