/*
Author:
Charles Wood
7-2-2020
*/

#pragma once
#include "pch.h"

class FontFixed {
public:
	virtual void DrawText(const std::string& str, int x, int y) = 0;
	virtual int TextLength(const std::string& str, int at = INT32_MAX) = 0;
	virtual int DrawLetter(char c, int x, int y) = 0;
	virtual int GetHeight() = 0;
	virtual std::string FontName() = 0;
	virtual ~FontFixed() {
		std::cout << "Destroy Font Fixed";
	}
};



/// <summary>
/// Draws and measures a 32 px font
/// </summary>
class Font16 : public FontFixed {
public:
	void DrawText(const std::string &str, int x, int y);
	int TextLength(const std::string &str, int at = INT32_MAX);
	int DrawLetter(char c, int x, int y);
	int GetHeight() ;
	std::string FontName() { return "FONT16"; }
	virtual ~Font16() {																													
		std::cout << "Destroy Font16";
	}

};	


/// <summary>
/// Draws and measures a 32 px font
/// </summary>
class Font32: public FontFixed {
public:
	void DrawText(const std::string& str, int x, int y);
	int TextLength(const std::string& str, int at = INT32_MAX);
	int DrawLetter(char c, int x, int y);
	int GetHeight();
	std::string FontName() { return "FONT32"; }
	virtual ~Font32() {
		std::cout << "Destroy Font32";
	}
};



