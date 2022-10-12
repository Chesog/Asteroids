#include "options.h"

extern Music menuMusic;

int optionsLoop(bool& backToMenu, int& screenWidth, int& screenHeight)
{
	UpdateMusicStream(menuMusic);

	int mainMenu = 0;
	int optionsMenu = 3;
	static int point = 1;
	int resolutionSelection = checkInputOptions(backToMenu, point);

	Rectangle defaultResolution;
	Rectangle maxResolution;
	createOptionsButtons(defaultResolution, maxResolution);

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
	drawOptions(point, defaultResolution, maxResolution);
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
		backToMenu = false;
		return defaultValue;
	}
}
void drawOptions(int point, Rectangle defaultResolution, Rectangle maxResolution)
{
	int fontSize = 30;

	ClearBackground(BLACK);
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
	DrawText("1280 X 720", GetScreenWidth() / 2 - textSize1 / 2, GetScreenHeight() / 2 - 30, fontSize, BLACK);

	if (point == (int)OptionsResolution::MaxResolution)
	{
		DrawRectangleRec(maxResolution, GREEN);
	}
	else if (point != (int)OptionsResolution::MaxResolution)
	{
		DrawRectangleRec(maxResolution, RED);
	}
	DrawText("1920 X 1080", GetScreenWidth() / 2 - textSize2 / 2, GetScreenHeight() / 2 + 30, fontSize, BLACK);
}
void createOptionsButtons(Rectangle& defaultResolution, Rectangle& maxResolution)
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
