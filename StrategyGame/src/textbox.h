#pragma once
#include "pch.h"
#include "visualbase.h"

class TextBox : public VisualBase {
public:
	TextBox(int x, int y, int w, int h);
	void SetText(std::string val);
	std::string GetText();
	void SetTexture(SDL_Texture* tex);
	void SetOnClick(std::function<void(void)> func);
	void MouseIn() override;
	void MouseOut() override;
	void MouseDown(int mx, int my) override;
	void MouseUp() override;
	void Draw() override;
	void MouseClick(int mx, int my) override;
	void Process(double ms) override;
	void KeyIn(int key);
	inline void SetCaps(bool val) { allCaps = val; };
	inline void SetLetters(std::string val) { allowedChars = val; };
	inline void SetMaxLength(size_t val) { maxLen = val; };
protected:
	bool allCaps;
	std::string allowedChars{ "" };
	size_t maxLen = 256;
	double curTime = 0;
	bool showCursor{ false };
	int curX = 0;
	std::function<void(void)> onClick;
	SDL_Texture* texture = nullptr;
	std::string label{ "" };
};

