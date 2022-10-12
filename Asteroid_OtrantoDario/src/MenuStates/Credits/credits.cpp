#include "credits.h"

extern Music menuMusic;
Texture2D CreditsBackground;

int creditsLoop(bool& backToMenu)
{
	UpdateMusicStream(menuMusic);

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
	Vector2 backgroundPosition = { 0.0f,0.0f };
	float scale = 1.0f;

	ClearBackground(BLACK);
	DrawTextureEx(CreditsBackground,backgroundPosition,0, scale,WHITE);
}
void checkInput(bool& backToMenu)
{
	if (IsKeyReleased(KEY_ESCAPE))
	{
		backToMenu = true;
	}
}
