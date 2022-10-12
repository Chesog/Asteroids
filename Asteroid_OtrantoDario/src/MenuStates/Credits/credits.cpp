#include "credits.h"

extern Music menuMusic;
extern Texture2D returnTexture;

static Button returnButton;

Texture2D CreditsBackground;


int creditsLoop(bool& backToMenu)
{
	UpdateMusicStream(menuMusic);

	int buttonWidth = 100;
	int buttonHeight = 40;
	returnButton = initButton(GetScreenWidth() -static_cast<int>(buttonWidth * 2.5f),buttonHeight ,10,buttonWidth,buttonHeight,0,"Return",GREEN,RED);

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
	drawButtonTexture(returnButton, returnTexture, returnTexture);
}
void checkInput(bool& backToMenu)
{
	Vector2 mousePosition = { static_cast<float>(GetMouseX()),static_cast<float>(GetMouseY()) };

	if (IsKeyReleased(KEY_ESCAPE))
	{
		backToMenu = true;
	}
	if (CheckCollisionPointRec(mousePosition, returnButton.rect))
	{
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) 
		{
			backToMenu = true;
		}
	}
}
