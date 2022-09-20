#include "gameplay.h"

void drawGameplay();
void updateGameplay();

int gameplayLoop(bool& initGame) 
{
	static SpaceShip player;
	if (initGame)
	{
		player = initSpaceShip();
		initGame = false;
	}


	drawGameplay();


	return (int)MenuStates::Gameplay;
}
void drawGameplay() 
{
	BeginDrawing();
	ClearBackground(BLACK);
	//DrawRectanglePro():
	
	EndDrawing();
}
void updateGameplay() 
{

}