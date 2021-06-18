#pragma once
#include "pch.h"
#include "visualbase.h"

class Label : public VisualBase {
public:
	Label(int x, int y, int w, int h);
	Label(SDL_Rect pos);
	void SetText(std::string val);
	void SetTexture(SDL_Texture* tex);
	void SetOnClick(std::function<void(void)> func);
	void MouseIn() override;
	void MouseOut() override;
	void MouseDown(int mx, int my) override;
	void MouseUp() override;
	void Draw() override;
	void MouseClick(int mx, int my) override;
	void Process(double ms) override;
protected:
	std::function<void(void)> onClick;
	SDL_Texture* texture = nullptr;
	std::string label{ "" };
};

