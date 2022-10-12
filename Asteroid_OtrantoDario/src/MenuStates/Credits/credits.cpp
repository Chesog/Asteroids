#include "credits.h"

extern Music menuMusic;
extern Texture2D returnTexture;

extern Texture2D mouseTexture;

static Button returnButton;
static Button linkButtonDario;
static Button linkButtonMartu;
static Button linkButtonTofy;
static Button linkButtonSeba;
static Button linkButtonEnzo;

Texture2D CreditsBackground;
Texture2D CreditsBackground2;
Texture2D gitTexture;
Texture2D gitTextureSelection;
Texture2D instagramTexture;
Texture2D instagramTextureSelection;


int creditsLoop(bool& backToMenu)
{
	UpdateMusicStream(menuMusic);

	int buttonWidth = 100;
	int buttonHeight = 40;

	int originalResWhidth = 1024;
	int originalResHeight = 768;

	returnButton = initButton(GetScreenWidth() - static_cast<int>(buttonWidth * 2.5f), buttonHeight, 10, buttonWidth, buttonHeight, 0, "Return", GREEN, RED);

	if (GetScreenWidth() != originalResWhidth && GetScreenHeight() != originalResHeight)
	{
		linkButtonDario = initButton(static_cast<int>(buttonWidth * 2.5f), static_cast<int>(buttonHeight * 5.0f), 10, buttonWidth, buttonHeight, 0, "Itch.IO", GREEN, RED);
		linkButtonMartu = initButton(static_cast<int>(buttonWidth * 2.5f), static_cast<int>(buttonHeight * 8.5f), 10, buttonWidth, buttonHeight, 0, "Instagram", GREEN, RED);
		linkButtonTofy = initButton(static_cast<int>(buttonWidth * 2.5f), static_cast<int>(buttonHeight * 10.5f), 10, buttonWidth, buttonHeight, 0, "Instagram", GREEN, RED);
		linkButtonSeba = initButton(static_cast<int>(buttonWidth * 2.5f), static_cast<int>(buttonHeight * 12.0f), 10, buttonWidth, buttonHeight, 0, "Instagram", GREEN, RED);
		linkButtonEnzo = initButton(static_cast<int>(buttonWidth * 2.5f), static_cast<int>(buttonHeight * 15.5f), 10, buttonWidth, buttonHeight, 0, "Itch.IO", GREEN, RED);
	}
	else
	{
		linkButtonDario = initButton(buttonWidth, static_cast<int>(buttonHeight * 5.5f), 10, buttonWidth, buttonHeight, 0, "Itch.IO", GREEN, RED);
		linkButtonMartu = initButton(buttonWidth, static_cast<int>(buttonHeight * 9.0f), 10, buttonWidth, buttonHeight, 0, "Instagram", GREEN, RED);
		linkButtonTofy = initButton(buttonWidth	, static_cast<int>(buttonHeight * 11.0f), 10, buttonWidth, buttonHeight, 0, "Instagram", GREEN, RED);
		linkButtonSeba = initButton(buttonWidth	, static_cast<int>(buttonHeight * 12.5f), 10, buttonWidth, buttonHeight, 0, "Instagram", GREEN, RED);
		linkButtonEnzo = initButton(buttonWidth	, static_cast<int>(buttonHeight * 16.0f), 10, buttonWidth, buttonHeight, 0, "Itch.IO", GREEN, RED);
	}



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
	int originalResWhidth = 1024;
	int originalResHeight = 768;

	ClearBackground(BLACK);

	if (GetScreenWidth() != originalResWhidth && GetScreenHeight() != originalResHeight)
	{
		DrawTextureEx(CreditsBackground2, backgroundPosition, 0, scale, WHITE);
	}
	else
	{
		DrawTextureEx(CreditsBackground, backgroundPosition, 0, scale, WHITE);
	}
	drawButtonTexture(returnButton, returnTexture, returnTexture);

	float scale1 = 2.5f;

	drawButtonTexture(linkButtonDario,gitTexture,gitTextureSelection, scale1);
	drawButtonTexture(linkButtonMartu, instagramTexture, instagramTextureSelection, scale1);
	drawButtonTexture(linkButtonTofy, instagramTexture, instagramTextureSelection, scale1);
	drawButtonTexture(linkButtonSeba, instagramTexture, instagramTextureSelection, scale1);
	drawButtonTexture(linkButtonEnzo, gitTexture, gitTextureSelection, scale1);

	DrawTextureEx(mouseTexture, GetMousePosition(), 0, 2.0f, WHITE);
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
	if (CheckCollisionPointRec(mousePosition,linkButtonDario.rect))
	{
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			OpenURL("https://github.com/Chesog");
		}
	}
	if (CheckCollisionPointRec(mousePosition, linkButtonMartu.rect))
	{
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			OpenURL("https://www.instagram.com/apitibon/");
		}
	}
	if (CheckCollisionPointRec(mousePosition, linkButtonTofy.rect))
	{
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			OpenURL("https://www.instagram.com/tofisdoodles/");
		}
	}
	if (CheckCollisionPointRec(mousePosition, linkButtonSeba.rect))
	{
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			OpenURL("https://github.com/Chesog");
		}
	}
	if (CheckCollisionPointRec(mousePosition, linkButtonEnzo.rect))
	{
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			OpenURL("https://github.com/BiscupidTea");
		}
	}
}
