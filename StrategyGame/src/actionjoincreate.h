/*
Author:
Charles Wood
7-3-2020
*/

#pragma once
#include "action.h"
#include "button.h"

#include "inputmanager.h"
#include "textbox.h"
#include "socketcallback.h"

class ActionJoinCreate : public Action {
public:
	ActionJoinCreate();
	~ActionJoinCreate();
	bool Process(double time);
	void Click();
	void Mouse(int x, int y, int b) override;
	void Draw();

protected:
	void joinClick();
	void createClick();
	void wanderClick();
private:
	MessageCallBack ourCallBack;
	bool first{ true };  //For turning on the message system....

	bool MessageIn(jute::jValue &val);
	void keyPressed(int val);
	TextBox* tRoomCode = nullptr;
	TextBox* tUserName = nullptr;
	//MouseManager* mouseMan = nullptr;
	InputManager keyMan;
	SDL_Rect location{ 0 };
	std::vector<VisualBase*> controls;
	std::string serverUrl = "";
	bool clicked = false;
	double eTime = 0;
	void draw();
};





