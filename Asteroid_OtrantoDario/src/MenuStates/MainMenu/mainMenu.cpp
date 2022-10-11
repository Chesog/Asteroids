#include "mainMenu.h"

Texture2D menu_Background;
Texture2D menu_Background1;

Texture2D playTexture;
Texture2D rulesTexture;
Texture2D optionsTexture;
Texture2D creditsTexture;
Texture2D exitTexture;

Texture2D menuLogo;

Music menuMusic;

int mainMenu(int& point)
{

	UpdateMusicStream(menuMusic);

	int fontSize = 30;
	int buttonWidth = 300;
	int buttonHeight = 40;
	int selection = 0;
	int selection2 = 0;
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	static Button button1 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) - buttonHeight * 4, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Gameplay, "Jugar", GREEN, RED);
	static Button button2 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) - buttonHeight * 2, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Rules, "Reglas", GREEN, RED);
	static Button button3 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2), fontSize, buttonWidth, buttonHeight, (int)MenuStates::Options, "Opciones", GREEN, RED);
	static Button button4 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 2, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Credits, "Creditos", GREEN, RED);
	static Button button5 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 4, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Exit, "Salir", GREEN, RED);
	Vector2 mousePosition = GetMousePosition();

	selection = checkInput(point);
	selection2 = checkMouseColition(mousePosition, button1, button2, button3, button4, button5, point);

	BeginDrawing();
	drawMenu(screenWidth, screenHeight, button1, button2, button3, button4, button5);
	EndDrawing();

	if (selection != 0)
	{
		return selection;
	}
	else
	{
		return selection2;
	}
}
int checkInput(int& point)
{
	int defaultOption = 0;
	if (IsKeyDown(KeyboardKey(KEY_UP)))
	{
		if (point <= (int)MenuStates::Gameplay)
		{
			point = (int)MenuStates::Exit;
		}
		else
		{
			point--;
		}
		return defaultOption;
	}
	else if (IsKeyDown(KeyboardKey(KEY_DOWN)))
	{
		if (point >= (int)MenuStates::Exit)
		{
			point = (int)MenuStates::Gameplay;
		}
		else
		{
			point++;
		}
		return defaultOption;
	}
	else if (IsKeyDown(KeyboardKey(KEY_ENTER)))
	{
		return point;
	}
	else if (IsKeyDown(KEY_ESCAPE))
	{
		return (int)MenuStates::Exit;
	}
	else
	{
		return defaultOption;
	}
}
void drawMenu(int screenWidth, int screenHeight, Button button1, Button button2, Button button3, Button button4, Button button5)
{
	float scale = 1.0f;

	int fontSize = 80;
	screenHeight = screenHeight;
	int textSizeTitle = MeasureText(TextFormat("Deep Purple"), fontSize);
	//int textSizeButton1 = MeasureText(TextFormat("JUGAR"), button1.fontSize);
	//int textSizeButton2 = MeasureText(TextFormat("REGLAS"), button2.fontSize);
	//int textSizeButton3 = MeasureText(TextFormat("OPCIONES"), button3.fontSize);
	//int textSizeButton4 = MeasureText(TextFormat("CREDITOS"), button4.fontSize);
	//int textSizeButton5 = MeasureText(TextFormat("SALIR"), button5.fontSize);
	Vector2 backgroundPosition = { 0.0f,0.0f };
	backgroundPosition.x = static_cast<float>(GetScreenWidth() / 2);
	backgroundPosition.y = static_cast<float>(GetScreenHeight() / 2);

	ClearBackground(BLACK);

	Rectangle sourRect = { 0,0,static_cast<float>(menu_Background1.width),static_cast<float>(menu_Background1.height) };
	Rectangle destRect = { backgroundPosition.x,backgroundPosition.y,static_cast<float>(menu_Background1.width * scale),static_cast<float>(menu_Background1.height * scale) };
	Vector2 texturePiv = { static_cast<float>((menu_Background1.width * scale) / 2),static_cast<float>((menu_Background1.height * scale) / 2) };

	DrawTexturePro(menu_Background1, sourRect, destRect, texturePiv, 0.0f, WHITE);

	//Rectangle sourRect1 = { 0,0,static_cast<float>(menu_Background.width),static_cast<float>(menu_Background.height) };
	//Rectangle destRect1 = { backgroundPosition.x,backgroundPosition.y,static_cast<float>(menu_Background.width * 1.5f * scale),static_cast<float>(menu_Background.height * scale) };
	//Vector2 texturePiv1 = { static_cast<float>((menu_Background.width * scale) / 2),static_cast<float>((menu_Background.height * scale) / 2) };
	//
	//DrawTexturePro(menu_Background, sourRect1, destRect1, texturePiv1, 0.0f, WHITE);

	DrawText("Deep Purple", (screenWidth / 2) - (textSizeTitle / 2), fontSize, fontSize, RED);

	drawButtonTexture(button1, playTexture, playTexture);
	//drawButton(button1);
	//DrawText("JUGAR", ((screenWidth / 2) - (textSizeButton1 / 2)), static_cast<int>((button1.rect.y + button1.rect.height / 6)), button1.fontSize, BLACK);

	drawButtonTexture(button2, rulesTexture, rulesTexture);
	//DrawText("REGLAS", ((screenWidth / 2) - (textSizeButton2 / 2)), static_cast<int>((button2.rect.y + button2.rect.height / 6)), button2.fontSize, BLACK);

	drawButtonTexture(button3, optionsTexture, optionsTexture);
	//DrawText("OPCIONES", ((screenWidth / 2) - (textSizeButton3 / 2)), static_cast<int>((button3.rect.y + button3.rect.height / 6)), button3.fontSize, BLACK);
	
	drawButtonTexture(button4, creditsTexture, creditsTexture);
	//DrawText("CREDITOS", ((screenWidth / 2) - (textSizeButton4 / 2)), static_cast<int>((button4.rect.y + button4.rect.height / 6)), button4.fontSize, BLACK);

	drawButtonTexture(button5, exitTexture, exitTexture);
	//DrawText("SALIR", ((screenWidth / 2) - (textSizeButton5 / 2)), static_cast<int>((button5.rect.y + button5.rect.height / 6)), button5.fontSize, BLACK);

#ifdef _DEBUG
	DrawRectangle(0, screenHeight / 2, screenWidth, 1, DARKGREEN);
	DrawRectangle(0, static_cast<int>((button1.rect.y + button1.rect.height / 2)), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>((button2.rect.y + button2.rect.height / 2)), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>((button3.rect.y + button3.rect.height / 2)), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>((button4.rect.y + button4.rect.height / 2)), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>((button5.rect.y + button5.rect.height / 2)), screenWidth, 1, BLUE);
	DrawRectangle(screenWidth / 2, 0, 1, screenHeight, DARKGREEN);
#endif // DEBUG
}
int checkMouseColition(Vector2 mousePosition, Button button1, Button button2, Button button3, Button button4, Button button5, int& point)
{
	if (CheckCollisionPointRec(mousePosition, button1.rect))
	{
		point = button1.optionNumber;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return button1.optionNumber;
		}
		else
		{
			return 0;
		}
	}
	else if (CheckCollisionPointRec(mousePosition, button2.rect))
	{
		point = button2.optionNumber;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return button2.optionNumber;
		}
		else
		{
			return 0;
		}
	}
	else if (CheckCollisionPointRec(mousePosition, button3.rect))
	{
		point = button3.optionNumber;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return button3.optionNumber;
		}
		else
		{
			return 0;
		}
	}
	else if (CheckCollisionPointRec(mousePosition, button4.rect))
	{
		point = button4.optionNumber;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return button4.optionNumber;
		}
		else
		{
			return 0;
		}
	}
	else if (CheckCollisionPointRec(mousePosition, button5.rect))
	{
		point = button5.optionNumber;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			return button5.optionNumber;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}