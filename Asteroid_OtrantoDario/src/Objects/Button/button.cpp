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
void drawButton(Button actualButton)
{
	Vector2 mousePosition = { static_cast<float>(GetMouseX()),static_cast<float>(GetMouseY()) };

	if (CheckCollisionPointRec(mousePosition, actualButton.rect))
	{
		DrawRectangle(static_cast<int>(actualButton.rect.x), static_cast<int>(actualButton.rect.y), static_cast<int>(actualButton.rect.width), static_cast<int>(actualButton.rect.height), actualButton.selectionColor);
	}
	else
	{
		DrawRectangle(static_cast<int>(actualButton.rect.x), static_cast<int>(actualButton.rect.y), static_cast<int>(actualButton.rect.width), static_cast<int>(actualButton.rect.height), actualButton.buttonColor);
	}
}