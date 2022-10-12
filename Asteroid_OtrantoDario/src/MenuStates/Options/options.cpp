#include "options.h"

Texture2D optionsBackground;

static Rectangle defaultResolution;
static Rectangle maxResolution;

static Button returnButton;
static Button togleFullScreen;

extern Texture2D returnTexture;
extern Music menuMusic;

int optionsLoop(bool& backToMenu, int& screenWidth, int& screenHeight)
{
	UpdateMusicStream(menuMusic);

	int buttonWidth = 100;
	int buttonHeight = 40;
	returnButton = initButton(GetScreenWidth() - static_cast<int>(buttonWidth * 2.5f), buttonHeight, 10, buttonWidth, buttonHeight, 0, "Return", GREEN, RED);
	togleFullScreen = initButton(GetScreenWidth() - static_cast<int>(GetScreenWidth() / 2 + buttonWidth * 1.5f), buttonHeight * 4, 10, buttonHeight, buttonHeight, 0, "Return", GREEN, RED);
	int mainMenu = 0;
	int optionsMenu = 3;
	static int point = 1;
	int resolutionSelection = checkInputOptions(backToMenu, point);


	createOptionsButtons();

	if (resolutionSelection == (int)OptionsResolution::DefaultResolution)
	{
		screenWidth = 1024;
		screenHeight = 768;
		SetWindowSize(screenWidth, screenHeight);
	}
	else if (resolutionSelection == (int)OptionsResolution::MaxResolution)
	{
		screenWidth = 1280;
		screenHeight = 720;
		SetWindowSize(screenWidth, screenHeight);
	}

	BeginDrawing();
	drawOptions(point);
	EndDrawing();

	if (backToMenu)
	{
		return mainMenu;
	}
	else
	{
		return optionsMenu;
	}
}
int checkInputOptions(bool& backToMenu, int& point)
{
	int defaultValue = 0;
	Vector2 mousePosition = { static_cast<float>(GetMouseX()),static_cast<float>(GetMouseY()) };


	if (CheckCollisionPointRec(mousePosition, returnButton.rect))
	{
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			backToMenu = true;
		}
	}

	if (CheckCollisionPointRec(mousePosition, defaultResolution))
	{
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			point = static_cast<int>(OptionsResolution::DefaultResolution);
			return point;
		}
	}


	if (CheckCollisionPointRec(mousePosition, maxResolution))
	{
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			point = static_cast<int>(OptionsResolution::MaxResolution);
			return point;
		}
	}

	if (CheckCollisionPointRec(mousePosition, togleFullScreen.rect))
	{
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			ToggleFullscreen();
		}
	}



	if (IsKeyReleased(KEY_UP))
	{
		if (point <= static_cast<int>(OptionsResolution::DefaultResolution))
		{
			point = static_cast<int>(OptionsResolution::MaxResolution);
		}
		else
		{
			point--;
		}
		return defaultValue;
	}
	if (IsKeyReleased(KEY_DOWN))
	{
		if (point >= static_cast<int>(OptionsResolution::MaxResolution))
		{
			point = static_cast<int>(OptionsResolution::DefaultResolution);
		}
		else
		{
			point++;
		}
		return defaultValue;
	}

	if (IsKeyReleased(KEY_ENTER))
	{
		return point;
	}

	if (IsKeyReleased(KEY_ESCAPE))
	{
		backToMenu = true;
		return defaultValue;
	}
	else
	{
		return defaultValue;
	}



}
void drawOptions(int point)
{
	int originalResWhidth = 1024;
	int originalResHeight = 768;

	int buttonWidth = 100;
	int buttonHeight = 40;

	Vector2 backgroundPosition = { 0.0f,0.0f };
	float scale = 0.0f;
	int fontSize = 30;

	Vector2 mousePosition = { static_cast<float>(GetMouseX()),static_cast<float>(GetMouseY()) };

	if (GetScreenWidth() != originalResWhidth && GetScreenHeight() != originalResHeight)
	{
		scale = 1.5f;
	}
	else
	{
		scale = 1.0f;
	}

	DrawTextureEx(optionsBackground, backgroundPosition, 0, scale, WHITE);
	drawButton(togleFullScreen);

	//int fullScreenText = MeasureText("Cambiar Pantalla Completa", fontSize);
	DrawText("Cambiar Pantalla Completa", GetScreenWidth() - static_cast<int>(GetScreenWidth() / 2 + buttonWidth), buttonHeight * 4,fontSize,BLACK);
	ClearBackground(BLACK);

	if (CheckCollisionPointRec(mousePosition, defaultResolution))
	{
		DrawRectangleRec(defaultResolution, YELLOW);
	}
	else
	{
		DrawRectangleRec(defaultResolution, RED);
	}

	if (CheckCollisionPointRec(mousePosition, maxResolution))
	{
		DrawRectangleRec(maxResolution, YELLOW);
	}
	else
	{
		DrawRectangleRec(maxResolution, RED);
	}

	if (point == (int)OptionsResolution::DefaultResolution)
	{
		DrawRectangleRec(defaultResolution, GREEN);
	}
	else if (point != (int)OptionsResolution::DefaultResolution)
	{
		DrawRectangleRec(defaultResolution, RED);
	}
	int textSize1 = MeasureText("1024 X 768", fontSize);
	int textSize2 = MeasureText("1280 X 720", fontSize);
	DrawText("1024 X 768", GetScreenWidth() / 2 - textSize1 / 2, GetScreenHeight() / 2 - 30, fontSize, BLACK);

	if (point == (int)OptionsResolution::MaxResolution)
	{
		DrawRectangleRec(maxResolution, GREEN);
	}
	else if (point != (int)OptionsResolution::MaxResolution)
	{
		DrawRectangleRec(maxResolution, RED);
	}
	DrawText("1280 X 720", GetScreenWidth() / 2 - textSize2 / 2, GetScreenHeight() / 2 + 45, fontSize, BLACK);

	drawButtonTexture(returnButton, returnTexture, returnTexture);
}
void createOptionsButtons()
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();
	defaultResolution.width = 300;
	defaultResolution.height = 40;
	defaultResolution.x = (screenWidth / 2) - defaultResolution.width / 2;
	defaultResolution.y = screenHeight / 2 - defaultResolution.height;

	maxResolution.width = 300;
	maxResolution.height = 40;
	maxResolution.x = (screenWidth / 2) - maxResolution.width / 2;
	maxResolution.y = screenHeight / 2 + maxResolution.height;

}
