#include "gameplay.h"
#include <iostream>

void drawGameplay(SpaceShip player);
void updateGameplay(SpaceShip& player);
void checkInput(SpaceShip& player);

int gameplayLoop(bool& initGame) 
{
	static SpaceShip player;
	if (initGame)
	{
		player = initSpaceShip();
		initGame = false;
	}

	checkInput(player);
	updateGameplay(player);
	drawGameplay(player);

	return (int)MenuStates::Gameplay;
}
void checkInput(SpaceShip& player)
{
	Vector2 distanceDiff;

	distanceDiff.x = GetMouseX() - player.rect.x;
	distanceDiff.y = GetMouseY() - player.rect.y;

	float angle = atan(distanceDiff.y / distanceDiff.x);
	angle = angle * 180 / PI;
	
	player.rotation = angle;

	Vector2 normalizedDirection;


	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		normalizedDirection = Vector2Normalize(distanceDiff);

		player.acceleration.x += normalizedDirection.x;
		player.acceleration.y += normalizedDirection.y;
	}
}
void drawGameplay(SpaceShip player)
{
	BeginDrawing();

	ClearBackground(BLACK);
	drawPlayer(player);
	
	EndDrawing();
}
void updateGameplay(SpaceShip& player) 
{
	moveSpaceShip(player);
}