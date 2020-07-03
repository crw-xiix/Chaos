#pragma once
#include "pch.h"
#include "visualbase.h"

/// <summary>
/// Owner is responsible for *items
/// </summary>
class MouseManager {
public:
	MouseManager(std::vector<VisBase*>* items);
	void Process(int mx, int my, int mb);
	~MouseManager();
private:
	std::vector<VisBase*>* viewItems = nullptr;
	VisBase* lastHover = nullptr;
	VisBase* lastDown = nullptr;
	int mouseDown = 0;
};

