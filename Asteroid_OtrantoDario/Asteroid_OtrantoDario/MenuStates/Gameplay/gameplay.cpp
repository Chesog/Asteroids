#include "gameplay.h"

void drawGameplay(SpaceShip player);
void updateGameplay(SpaceShip player);
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

	float normalizedDirectionX = distanceDiff.x / Vector2Length(distanceDiff);
	float normalizedDirectionY = distanceDiff.y / Vector2Length(distanceDiff);

	player.acceleration.x = 100;
	player.acceleration.y = 100;

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
	{
		moveSpaceShip(player);
	}
}
void drawGameplay(SpaceShip player)
{
	BeginDrawing();

	ClearBackground(BLACK);
	drawPlayer(player);
	
	EndDrawing();
}
void updateGameplay(SpaceShip player) 
{
	
}