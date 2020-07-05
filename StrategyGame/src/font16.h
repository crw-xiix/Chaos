/*
Author:
Charles Wood
7-2-2020
*/

#pragma once
#include "pch.h"

class Font16 {
public:
	static void DrawText(const std::string &str, int x, int y);
	static int TextLength(const std::string &str, int at = INT32_MAX);

	/// <summary>
	/// Draws a 16x16 letter, but smashed width wise
	/// </summary>
	/// <param name="c"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns>Number of pixels wide the character was</returns>
	static int DrawLetter(char c, int x, int y);
};


