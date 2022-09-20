#include "spaceship.h"
#include <iostream>


SpaceShip initSpaceShip() 
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	SpaceShip aux;

	aux.lives = 3;
	aux.score = 0;
	aux.rect.width = 35;
	aux.rect.height = 35;
	aux.rect.x = screenWidth / 2;
	aux.rect.y = screenHeight / 2;
	aux.piv.x = aux.rect.width / 2;
	aux.piv.y = aux.rect.height / 2;
	aux.rotation = 0.0f;
	aux.acceleration.x = 0;
	aux.acceleration.y = 0;
	return aux;
}

void moveSpaceShip(SpaceShip& player) 
{
	player.rect.x = player.rect.x + player.acceleration.x * GetFrameTime();
	player.rect.y = player.rect.y + player.acceleration.y * GetFrameTime();
}

void drawPlayer(SpaceShip& player)
{
	Vector2 origin;
	origin.x = player.rect.width / 2;
	origin.y = player.rect.height / 2;

	DrawRectanglePro(player.rect,player.piv, player.rotation, GREEN);
}

void shoot() 
{

}