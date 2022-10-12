#include "rules.h"

Texture2D Controls1;
Texture2D Controls2;
Texture2D rulesBackground;

static Button returnButton;

extern Texture2D returnTexture;
extern Music menuMusic;

int rulesLoop(bool& backToMenu)
{
	UpdateMusicStream(menuMusic);

	int menu = 0;
	int rules = 2;

	int buttonWidth = 100;
	int buttonHeight = 40;
	returnButton = initButton(GetScreenWidth() - static_cast<int>(buttonWidth * 2.5f), buttonHeight, 10, buttonWidth, buttonHeight, 0, "Return", GREEN, RED);

	checkInputR(backToMenu);
	drawRules();

	if (backToMenu)
	{
		return menu;
	}
	else
	{
		return rules;
	}
}
void drawRules()
{
	Vector2 backgroundPosition = { 0.0f,0.0f };
	int originalResWhidth = 1024;
	int originalResHeight = 768;

	float scale = 0.0f;

	if (GetScreenWidth() != originalResWhidth && GetScreenHeight() != originalResHeight) 
	{
		scale = 1.5f;
	}
	else
	{
		scale = 1.0f;
	}


	int tileFont = 40;
	int font = 30;
	int font2 = 20;
	int titleLenght = MeasureText("Reglas Deep Purple",font);
	int controls1Lenght = MeasureText("Disparar", font2);
	int controls2Lenght = MeasureText("Moverse", font2);
	int textSize3 = MeasureText("ESC PARA PAUSAR", font);
	int textSize4 = MeasureText("ESC PARA VOLVER PARA ATRAS (En los Menues)", font);

	BeginDrawing();
	ClearBackground(BLACK);

	DrawTextureEx(rulesBackground, backgroundPosition, 0, scale, WHITE);

	DrawText("Reglas Deep Purple",(GetScreenWidth() / 2) - (titleLenght / 2),static_cast<int>(tileFont * 2.5f), tileFont,GREEN);

	DrawTextureEx(Controls1, { static_cast<float>((GetScreenWidth() / 2) - Controls1.width / 3),static_cast<float>(Controls1.height / 4)},0.0f,0.2f,WHITE);
	DrawTextureEx(Controls2, { static_cast<float>((GetScreenWidth() / 2) + Controls2.width / 8),static_cast<float>(Controls2.height / 4)}, 0.0f,0.2f, WHITE);

	DrawText("Disparar",(GetScreenWidth() / 2) - Controls2.width / 3 - controls2Lenght / 2,Controls2.height / 4, font2, YELLOW);
	DrawText("Moverse",((GetScreenWidth() / 2) + Controls1.width / 3) - controls1Lenght / 2,Controls1.height / 4, font2, YELLOW);

	DrawText("ESC PARA PAUSAR", (GetScreenWidth() / 2) - (textSize3 / 2), (GetScreenHeight() / 2) + font , font, YELLOW);
	DrawText("ESC PARA VOLVER PARA ATRAS (En los Menues)", (GetScreenWidth() / 2) - (textSize4 / 2), (GetScreenHeight() / 2) + font * 2, font, YELLOW);
	DrawText("Deep Purple en una replica del Asteroids de 1979", font2, (GetScreenHeight() / 2) + font2 * 6, font2, YELLOW);
	DrawText("El juego consiste en mover la nave esquivando los asteroides", font2, (GetScreenHeight() / 2) + font2 * 7, font2, YELLOW);
	DrawText("Al disparar y romper uno de los asteroides este se dividira en 2 mas chicos", font2, (GetScreenHeight() / 2) + font2 * 8, font2, YELLOW);
	DrawText("expto por los mas chicos los cuales simplemente se rompen.", font2, (GetScreenHeight() / 2) + font2 * 9, font2, YELLOW);
	DrawText("Este juego consiste en un nivel infinito donde lo unico que se busca es ", font2, (GetScreenHeight() / 2) + font2 * 10, font2, YELLOW);
	DrawText("Superar tu propia puntuacion , eso si , despues de cierto puntaje", font2, (GetScreenHeight() / 2) + font2 * 11, font2, YELLOW);
	DrawText("Hay una sorpresa, Haceptas el reto ?", font2, (GetScreenHeight() / 2) + font2 * 12, font2, YELLOW);

	drawButtonTexture(returnButton, returnTexture, returnTexture);

	EndDrawing();
}
void checkInputR(bool& backToMenu)
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
