#include "pch.h"

class Action {
public:
	//Returns true if Process is complete.
	virtual bool Process(float time) = 0;
	virtual void Click() = 0;
};

class ActionPlayLocal : public Action {
	bool Process(float time);
	void Click();
};

class ActionMovePlayer : public Action {
	bool Process(float time);
	void Click();
};