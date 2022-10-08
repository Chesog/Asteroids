#include "credits.h"

int creditsLoop(bool& backToMenu)
{
	static int frameCounter = 0;
	static int lettersCount = 0;
	checkInput(backToMenu);

	BeginDrawing();
	drawCredits();
	EndDrawing();

	if (backToMenu)
	{
		return (int)MenuStates::MainMenu;
	}
	else
	{
		return (int)MenuStates::Credits;
	}
}
void drawCredits()
{
	int font = 80;
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();
	int testSize = MeasureText("CREADO POR", font);

	ClearBackground(BLACK);
	DrawText("CREADO POR", (screenWidth / 2) - (testSize / 2), (screenHeight / 2) - font, font, RED);
	DrawText("CHESO", (screenWidth / 2) - (testSize / 2), (screenHeight / 2), font, LIME);
}
void checkInput(bool& backToMenu)
{
	if (IsKeyReleased(KEY_ESCAPE))
	{
		backToMenu = true;
	}
}
