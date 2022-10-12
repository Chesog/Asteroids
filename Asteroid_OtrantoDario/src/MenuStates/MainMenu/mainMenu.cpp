#include "mainMenu.h"

Texture2D menu_Background;
Texture2D menu_Background1;

Texture2D playTexture;
Texture2D rulesTexture;
Texture2D optionsTexture;
Texture2D creditsTexture;
Texture2D exitTexture;

Texture2D mouseTexture;

Texture2D menuLogo;

Music menuMusic;

static Button button1;
static Button button2;
static Button button3;
static Button button4;
static Button button5;

extern int highScore;

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

	button1 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) , fontSize, buttonWidth, buttonHeight, (int)MenuStates::Gameplay, "Jugar", GREEN, RED);
	button2 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 2 , fontSize, buttonWidth, buttonHeight, (int)MenuStates::Rules, "Reglas", GREEN, RED);
	button3 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 4, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Options, "Opciones", GREEN, RED);
	button4 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 6, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Credits, "Creditos", GREEN, RED);
	button5 = initButton(((screenWidth / 2) - (buttonWidth / 2)), (screenHeight / 2) + buttonHeight * 8, fontSize, buttonWidth, buttonHeight, (int)MenuStates::Exit, "Salir", GREEN, RED);
	Vector2 mousePosition = GetMousePosition();

	selection = checkInput(point);
	selection2 = checkMouseColition(mousePosition, point);

	BeginDrawing();
	drawMenu(screenWidth, screenHeight);
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
void drawMenu(int screenWidth, int screenHeight)
{
	//DrawTexture(mouseTexture,static_cast<int>(GetMouseX()), static_cast<int>(GetMouseY()),WHITE);
	
	float scale = 1.0f;
	int originalResWhidth = 1024;
	int originalResHeight = 768;

	Vector2 backgroundPosition = { 0.0f,0.0f };

	ClearBackground(BLACK);

	if (GetScreenWidth() != originalResWhidth && GetScreenHeight() != originalResHeight)
	{
		scale = 1.5f;
	}
	else
	{
		scale = 1.0f;
	}

	int fontSize = 80;
	screenHeight = screenHeight;
	screenWidth = screenWidth;

	ClearBackground(BLACK);

	DrawTextureEx(menu_Background1, backgroundPosition, 0, scale, WHITE);

	float scale1 = 0.0f;

	if (GetScreenWidth() != originalResWhidth && GetScreenHeight() != originalResHeight)
	{
		scale1 = 0.5f;
	}
	else
	{
		scale1 = 0.3f;
	}

	Vector2 logoPosition = { 0.0f,0.0f };
	logoPosition.x = static_cast<float>(GetScreenWidth() / 2) - (menuLogo.width / 4) * scale1;
	logoPosition.y = static_cast<float>(fontSize * 2);

	Rectangle sourRect1 = { 0,0,static_cast<float>(menuLogo.width),static_cast<float>(menuLogo.height) };
	Rectangle destRect1 = { logoPosition.x,logoPosition.y,static_cast<float>(menuLogo.width * 1.5f * scale1),static_cast<float>(menuLogo.height * scale1) };
	Vector2 texturePiv1 = { static_cast<float>((menuLogo.width * scale1) / 2),static_cast<float>((menuLogo.height * scale1) / 2) };
	
	DrawTexturePro(menuLogo, sourRect1, destRect1, texturePiv1, 0.0f, WHITE);

	drawButtonTexture(button1, playTexture, playTexture);

	drawButtonTexture(button2, rulesTexture, rulesTexture);

	drawButtonTexture(button3, optionsTexture, optionsTexture);
	
	drawButtonTexture(button4, creditsTexture, creditsTexture);

	drawButtonTexture(button5, exitTexture, exitTexture);



#ifdef _DEBUG
	DrawRectangle(0, screenHeight / 2, screenWidth, 1, DARKGREEN);
	DrawRectangle(0, static_cast<int>((button1.rect.y + button1.rect.height / 2)), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>((button2.rect.y + button2.rect.height / 2)), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>((button3.rect.y + button3.rect.height / 2)), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>((button4.rect.y + button4.rect.height / 2)), screenWidth, 1, BLUE);
	DrawRectangle(0, static_cast<int>((button5.rect.y + button5.rect.height / 2)), screenWidth, 1, BLUE);
	DrawRectangle(screenWidth / 2, 0, 1, screenHeight, DARKGREEN);
#endif // DEBUG

	if (highScore != 0)
	{
		int font = 40;
		int textSize = MeasureText(TextFormat("Max Score : %i", highScore), font);
		DrawText(TextFormat("Max Score : %i", highScore),GetScreenWidth() / 2 + textSize / 2, font, font, PURPLE);
	}

	DrawTextureEx(mouseTexture, GetMousePosition(), 0, 2.0f, WHITE);
}
int checkMouseColition(Vector2 mousePosition, int& point)
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