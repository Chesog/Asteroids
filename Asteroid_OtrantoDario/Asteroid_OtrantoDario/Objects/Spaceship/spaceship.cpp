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
	aux.normalizedDirection = { 0,0 };
	aux.acceleration.x = 0;
	aux.acceleration.y = 0;
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		aux.playerAmmo[i].position = { 0,0 };
		aux.playerAmmo[i].trayectory = {0,0};
		aux.playerAmmo[i].speed = {500.0f,500.0f};
		aux.playerAmmo[i].rad = 4.0f;
		aux.playerAmmo[i].isActive = false;
		aux.playerAmmo[i].color = RED;
	}
	return aux;
}

void moveSpaceShip(SpaceShip& player)
{
	player.rect.x = player.rect.x + player.acceleration.x * 6 * GetFrameTime();
	player.rect.y = player.rect.y + player.acceleration.y * 6 * GetFrameTime();
}

void drawPlayer(SpaceShip& player)
{
	DrawRectanglePro(player.rect, player.piv, player.rotation, GREEN);
}

void shoot(Bullet& bullet, SpaceShip player)
{
	bullet.position.x = player.rect.x;
	bullet.position.y = player.rect.y;
	bullet.trayectory = player.normalizedDirection;

	bullet.isActive = true;
	bullet.rotation = player.rotation;
}