#pragma once
#include "pch.h"
#include "unit.h"

class Action {
public:
	//Returns true if Process is complete.
	virtual bool Process(double time) = 0;
	virtual void Click() = 0;
	virtual void Mouse(int mx, int my, int b);
	inline std::list<Action*> GetNext() { return nextActions; }
	Action();
protected: 

	std::list<Action*> nextActions;
private:
	

};

class ActionPlayLocal : public Action {
	bool Process(double time);
	void Click();
};


class ActionMovePlayer : public Action {
	int tx, ty;
	Unit& actor;
public:
	ActionMovePlayer(Unit& who, int x, int y);
	bool Process(double time);
	void Click();
};


//XXXC CRW  Need action request, action join, action waiting, action playing and action 
//game over.  Also have to do point inserts on action lists.
