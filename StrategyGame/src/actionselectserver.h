#pragma once
#include "action.h"

class ActionSelectServer : public Action {
public:
	ActionSelectServer();
	bool Process(double time);
	void Click();
	void Mouse(int x, int y, int b) override;
private:
	std::vector<SDL_Rect> areas;
	std::string serverUrl = "";
	bool clicked = false;
	double eTime = 0;
	void draw();

};

