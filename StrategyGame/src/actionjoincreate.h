/*
Author:
Charles Wood
7-3-2020
*/

#pragma once
#include "action.h"
#include "button.h"
#include "mousemanager.h"
#include "keymanager.h"
#include "textbox.h"

class ActionJoinCreate : public Action {
public:
	ActionJoinCreate();
	~ActionJoinCreate();
	bool Process(double time);
	void Click();
	void Mouse(int x, int y, int b) override;

protected:
	void joinClick();
	void createClick();
	void backClick();
private:
	void MessageIn(std::string val);
	void keyPressed(int val);
	TextBox* tRoomCode = nullptr;
	MouseManager* mouseMan = nullptr;
	KeyboardManager keyMan;
	SDL_Rect location{ 0 };
	std::vector<VisBase*> controls;
	std::string serverUrl = "";
	bool clicked = false;
	double eTime = 0;
	void draw();
};





