#pragma once
#include "action.h"

class ActionIntro : public Action {
public:
	ActionIntro();
	bool Process(double time);
	void Click();
private:
	bool clicked = false;
	SDL_Texture* tex = nullptr;
	double eTime = 0;
};
