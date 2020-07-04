#pragma once
#include "pch.h"
#include "visualbase.h"

class Label : public VisBase {
public:
	Label(int x, int y, int w, int h);
	void SetText(std::string val);
	void SetTexture(SDL_Texture* tex);
	void SetOnClick(std::function<void(void)> func);
	void MouseIn() override;
	void MouseOut() override;
	void MouseDown() override;
	void MouseUp() override;
	void Draw() override;
	void MouseClick(int mx, int my) override;
protected:
	std::function<void(void)> onClick;
	SDL_Texture* texture = nullptr;
	std::string label{ "" };
};

