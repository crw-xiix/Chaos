#pragma once
#include "pch.h"
#include "visualbase.h"

/// <summary>
/// Owner is responsible for *items
/// </summary>
class MouseManager {
public:
	MouseManager(std::vector<VisualBase*>* items);
	void Process(int mx, int my, int mb);
	~MouseManager();
private:
	std::vector<VisualBase*>* viewItems = nullptr;
	VisualBase* lastHover = nullptr;
	VisualBase* lastDown = nullptr;
	int mouseDown = 0;
};

