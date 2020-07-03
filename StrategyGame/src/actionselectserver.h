#pragma once
#include "action.h"
#include "button.h"

class MouseManager {
public:
	MouseManager(std::vector<VisBase*> *items);
	void Process(int mx, int my, int mb);
private:
	std::vector<VisBase*> *viewItems;
	VisBase* lastHover = nullptr;
	VisBase* lastDown = nullptr;
	int mouseDown = 0;
	
};

class ActionSelectServer : public Action {
public:
	ActionSelectServer();
	bool Process(double time);
	void Click();
	void Mouse(int x, int y, int b) override;
	std::string Url;
protected:
	void localClick();
	void remoteClick();
	void quitClick();
private:
	MouseManager *mouseMan;
	SDL_Rect location;
	std::vector<VisBase*> controls;
	std::string serverUrl = "";
	bool clicked = false;
	double eTime = 0;
	void draw();
};

