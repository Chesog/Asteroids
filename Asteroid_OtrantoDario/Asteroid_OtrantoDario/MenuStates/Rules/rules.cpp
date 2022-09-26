#include "rules.h"

int rulesLoop(bool& backToMenu, Color colorPlayer1, Color colorPlayer2)
{
	int menu = 0;
	int rules = 2;

	checkInputR(backToMenu);

	BeginDrawing();
	drawRules(colorPlayer1, colorPlayer2);
	EndDrawing();
	if (backToMenu)
	{
		return menu;
	}
	else
	{
		return rules;
	}
}
void drawRules(Color colorPlayer1, Color colorPlayer2)
{
	int screeWidht = GetScreenWidth();
	int screeHeight = GetScreenHeight();
	int font = 30;
	int font2 = 20;
	int textSize1 = MeasureText("Controles Player Izquierdo", font);
	int textSize2 = MeasureText("Controles Player Derecho", font);
	int textSize3 = MeasureText("ESPACIO PARA PAUSAR", font);
	int textSize4 = MeasureText("ESC PARA VOLVER PARA ATRAS", font);

	ClearBackground(BLACK);
	DrawText("Controles Player Izquierdo", (screeWidht / 2) - (textSize1 + font), font, font, colorPlayer2);
	DrawText("W", (screeWidht / 2) - (textSize1 / 2), font * 2, font, colorPlayer2);
	DrawText("S", (screeWidht / 2) - (textSize1 / 2), font * 3, font, colorPlayer2);
	DrawText("Controles Player Derecho", (screeWidht / 2) + font, font, font, colorPlayer1);
	DrawText("Arrow Up", (screeWidht / 2) + (textSize1 / 2), font * 2, font, colorPlayer1);
	DrawText("Arrow Down", (screeWidht / 2) + (textSize1 / 2), font * 3, font, colorPlayer1);

	DrawText("ESPACIO PARA PAUSAR", (screeWidht / 2) - (textSize3 / 2), (screeHeight / 2) + font, font, YELLOW);
	DrawText("ESC PARA VOLVER PARA ATRAS", (screeWidht / 2) - (textSize4 / 2), (screeHeight / 2) - font * 2, font, YELLOW);
	DrawText("Pong es un juego de deportes en dos dimensiones que simula un tenis de mesa.", font2, (screeHeight / 2) + font2 * 6, font2, YELLOW);
	DrawText("El jugador controla en el juego una paleta moviendola verticalmente en la parte izquierda de la pantalla,", font2, (screeHeight / 2) + font2 * 7, font2, YELLOW);
	DrawText("y puede competir tanto contra un oponente controlado por computadora,", font2, (screeHeight / 2) + font2 * 8, font2, YELLOW);
	DrawText("como con otro jugador humano que controla una segunda paleta en la parte opuesta.", font2, (screeHeight / 2) + font2 * 9, font2, YELLOW);
	DrawText("Los jugadores pueden usar las paletas para pegarle a la pelota hacia un lado u otro.", font2, (screeHeight / 2) + font2 * 10, font2, YELLOW);
	DrawText("El objetivo consiste en que uno de los jugadores consiga 10 puntos para finalizar el juego.", font2, (screeHeight / 2) + font2 * 11, font2, YELLOW);
	DrawText("Estos puntos se obtienen cuando el jugador adversario falla al devolver la pelota", font2, (screeHeight / 2) + font2 * 12, font2, YELLOW);
}
void checkInputR(bool& backToMenu)
{
	if (IsKeyPressed(KEY_ESCAPE))
	{
		backToMenu = true;
	}
}
