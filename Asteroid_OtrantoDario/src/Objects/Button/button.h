#pragma once
#include "raylib.h"
#include <string>

using namespace std;
namespace cheso_Asteroids
{
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
	void drawButton(Button actualButton);
	void drawButtonTexture(Button actualButton, Texture2D buttonTexture, Texture2D selectionTexture);
	void drawButtonTexture(Button actualButton, Texture2D buttonTexture, Texture2D selectionTexture, float scale);
}