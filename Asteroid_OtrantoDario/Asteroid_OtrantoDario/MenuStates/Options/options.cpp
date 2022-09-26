#include "options.h"

int optionsLoop(bool& backToMenu, int& screenWidth, int& screenHeight)
{
	int mainMenu = 0;
	int optionsMenu = 3;
	static int point = 1;
	int resolutionSelection = checkInputOptions(backToMenu, point);

	Rectangle defaultResolution;
	Rectangle maxResolution;
	createOptionsButtons(defaultResolution, maxResolution);

	if (resolutionSelection == (int)OptionsResolution::DefaultResolution)
	{
		screenWidth = 1280;
		screenHeight = 720;
		SetWindowSize(screenWidth, screenHeight);
		ToggleFullscreen();
	}
	else if (resolutionSelection == (int)OptionsResolution::MaxResolution)
	{
		screenWidth = 1920;
		screenHeight = 1080;
		SetWindowSize(screenWidth, screenHeight);
		ToggleFullscreen();
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
	if (IsKeyPressed(KEY_UP))
	{
		if (point <= (int)OptionsResolution::DefaultResolution)
		{
			point = (int)OptionsResolution::MaxResolution;
		}
		else
		{
			point--;
		}
		return 0;
	}
	else if (IsKeyPressed(KEY_DOWN))
	{
		if (point >= (int)OptionsResolution::MaxResolution)
		{
			point = (int)OptionsResolution::DefaultResolution;
		}
		else
		{
			point++;
		}
		return 0;
	}

	else if (IsKeyPressed(KEY_ENTER))
	{
		return point;
	}

	if (IsKeyPressed(KEY_ESCAPE))
	{
		backToMenu = true;
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
	int textSize1 = MeasureText("1280 X 720", fontSize);
	int textSize2 = MeasureText("1920 X 1080", fontSize);
	DrawText("1280 X 720", GetScreenWidth() / 2 - textSize1 / 2, GetScreenHeight() / 2 - 30, fontSize, BLACK);

	if (point == (int)OptionsResolution::MaxResolution)
	{
		DrawRectangleRec(maxResolution, GREEN);
	}
	else if (point != (int)OptionsResolution::MaxResolution)
	{
		DrawRectangleRec(maxResolution, RED);
	}
	DrawText("1920 X 1080", GetScreenWidth() / 2 - textSize1 / 2, GetScreenHeight() / 2 + 30, fontSize, BLACK);
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
