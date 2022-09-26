#pragma once
#include "raylib.h"
#include <string>

using namespace std;

struct Button
{
	int fontSize;
	int optionNumber;
	string text;
	Color buttonColor;
	Color selectionColor;
	Rectangle rect;
};

Button initButton(int initialPosX, int initialPosY, int fontSize, int buttonWidth, int buttonHeight, int optionNumber, string text, Color buttonColor, Color selectionColor);
