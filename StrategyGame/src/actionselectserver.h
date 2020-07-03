#pragma once
#include "action.h"
#include "button.h"

class MouseManager {
public:
	MouseManager(std::vector<VisBase*> *items);
	void Process(int mx, int my, int mb);
private:
	std::vector<VisBase*>* viewItems = nullptr;
	VisBase* lastHover = nullptr;
	VisBase* lastDown = nullptr;
	int mouseDown = 0;
};

class ActionSelectServer : public Action {
public:
	ActionSelectServer();
	~ActionSelectServer();
	bool Process(double time);
	void Click();
	void Mouse(int x, int y, int b) override;
	
protected:
	void localClick();
	void remoteClick();
	void quitClick();
private:
	std::string Url{ "" };
	MouseManager* mouseMan = nullptr;
	SDL_Rect location{ 0 };
	std::vector<VisBase*> controls;
	std::string serverUrl = "";
	bool clicked = false;
	double eTime = 0;
	void draw();
};

