#pragma once
#include "pch.h"
#include "unit.h"

class Action {
public:
	//Returns true if Process is complete.
	virtual bool Process(double time);
	virtual void Draw();
	virtual void Click();
	virtual void Mouse(int mx, int my, int b);
	//Once this gets called, it's a unique_ptr, do not delete here.
	Action* GetNext() { return nextAction; }
	virtual inline bool HasKeyboardControl() { return true; };
	Action();
	virtual ~Action();
protected: 
	Action* nextAction = nullptr;
private:
};

class ActionPlayLocal : public Action {
	bool Process(double time);
	void Click();
};


class ActionMovePlayer : public Action {
public:
	ActionMovePlayer(Unit& who, int x, int y);
	bool HasKeyboardControl() override;
	bool Process(double time);
	void Click();
	void Draw() override;
private:
	int targetX, targetY;
	Unit& actor;
};

