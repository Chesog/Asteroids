#include "button.h"

Button initButton(int initialPosX, int initialPosY, int fontSize, int buttonWidth, int buttonHeight, int optionNumber, string text, Color buttonColor, Color selectionColor)
{
	Button aux;
	aux.rect.x = initialPosX;
	aux.rect.y = initialPosY;
	aux.fontSize = fontSize;
	aux.rect.width = buttonWidth;
	aux.rect.height = buttonHeight;
	aux.optionNumber = optionNumber;
	aux.text = text;
	aux.buttonColor = buttonColor;
	aux.selectionColor = selectionColor;
	return aux;
}