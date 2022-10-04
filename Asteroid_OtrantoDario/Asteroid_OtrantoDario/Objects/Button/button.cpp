#include "button.h"

Button initButton(int initialPosX, int initialPosY, int fontSize, int buttonWidth, int buttonHeight, int optionNumber, string text, Color buttonColor, Color selectionColor)
{
	Button aux;
	aux.rect.x = static_cast<float>(initialPosX);
	aux.rect.y = static_cast<float>(initialPosY);
	aux.fontSize = fontSize;
	aux.rect.width = static_cast<float>(buttonWidth);
	aux.rect.height = static_cast<float>(buttonHeight);
	aux.optionNumber = optionNumber;
	aux.text = text;
	aux.buttonColor = buttonColor;
	aux.selectionColor = selectionColor;
	return aux;
}