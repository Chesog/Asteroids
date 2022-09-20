#include "spaceship.h"

SpaceShip initSpaceShip() 
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	SpaceShip aux;
	aux.currentDirectionX = (int)Directions::Stop;
	aux.currentDirectionY = (int)Directions::Stop;
	aux.posX = screenWidth / 2;
	aux.posY = screenHeight / 2;
	aux.lives = 3;
	aux.score = 0;
	aux.rect.width = 35;
	aux.rect.height = 35;
	aux.rect.x = aux.posX - aux.rect.width / 2;
	aux.rect.y = aux.posY - aux.rect.height / 2;
	return aux;
}

void moveSpaceShip(SpaceShip& player) 
{
	Vector2 cursor = GetMousePosition();
	Vector2 distanceDiff;

	distanceDiff.x = player.posX - cursor.x;
	distanceDiff.y = player.posY - cursor.y;

	if (player.currentDirectionX == (int)Directions::Left || player.currentDirectionX == (int)Directions::Right)
	{
		player.posX -= distanceDiff.x * GetFrameTime();
	}

	if (player.currentDirectionY == (int)Directions::Up || player.currentDirectionY == (int)Directions::Down)
	{
		player.posY -= distanceDiff.y * GetFrameTime();
	}

	if (player.currentDirectionX == (int)Directions::Stop || player.currentDirectionY == (int)Directions::Stop)
	{
		player.posX;
		player.posY;
	}
}

void shoot() 
{

}