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
