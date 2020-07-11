/*
Author:
Charles Wood
7-2-2020
*/

#pragma once
#include "action.h"
#include "button.h"
#include "mousemanager.h"

class ActionSelectServer : public Action {
public:
	ActionSelectServer();
	~ActionSelectServer();
	bool Process(double time);
	void Click();
	void Mouse(int x, int y, int b) override;
	void Draw() override;
protected:
	//event handlers
	void localClick();
	void remoteClick();
	void quitClick();
private:
	
	MouseManager* mouseMan = nullptr;
	SDL_Rect location{ 0 };
	std::vector<VisualBase*> controls;
	bool clicked = false;
	double eTime = 0;
};

