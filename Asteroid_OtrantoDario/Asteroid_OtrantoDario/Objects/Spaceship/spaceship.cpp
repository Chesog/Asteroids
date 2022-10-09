#include "spaceship.h"
#include <iostream>


SpaceShip initSpaceShip(Texture2D spaceshipTexture,Texture2D bulletTexture)
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	SpaceShip aux;

	aux.lives = 3;
	aux.score = 0;
	aux.rad = 20.0f;
	aux.rect.width = aux.rad;
	aux.rect.height = aux.rad;
	aux.rect.x = static_cast<float>(screenWidth / 2);
	aux.rect.y = static_cast<float>(screenHeight / 2);
	aux.piv.x = aux.rect.width / 2;
	aux.piv.y = aux.rect.height / 2;
	aux.rotation = 0.0f;
	aux.normalizedDirection = { 0,0 };
	aux.acceleration.x = 0.0f;
	aux.acceleration.y = 0.0f;
	aux.spaceshipTexture = spaceshipTexture;
	aux.isHit = false;
	aux.spaceshipColor = WHITE;
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		initBullet(aux.playerAmmo[i],bulletTexture);
	}
	return aux;
}

void moveSpaceShip(SpaceShip& player)
{
	player.rect.x = player.rect.x + player.acceleration.x * 0.5f * GetFrameTime();
	player.rect.y = player.rect.y + player.acceleration.y * 0.5f * GetFrameTime();
}

void drawPlayer(SpaceShip& player)
{
#if _DEBUG
	DrawCircle(static_cast<int>(player.rect.x), static_cast<int>(player.rect.y),player.rad,GREEN);
#endif // _DEBUG

	if (player.isHit)
	{
		int rand = GetRandomValue(0,2);
		if (rand == 0)
		{
			player.spaceshipColor.a = 100;
		}
		else
		{
			player.spaceshipColor.a = 250;
		}
	}
	if (!player.isHit)
	{
		player.spaceshipColor.a = 250;
	}

	Rectangle sourRect = {0.0f,0.0f,static_cast<float>(player.spaceshipTexture.width),static_cast<float>(player.spaceshipTexture.height)};
	Rectangle destRect = {player.rect.x,player.rect.y,sourRect.width,sourRect.height};
	Vector2 texturePiv = { static_cast<float>(player.spaceshipTexture.width / 2),static_cast<float>(player.spaceshipTexture.height / 2)};

	DrawTexturePro(player.spaceshipTexture,sourRect,destRect, texturePiv,player.rotation + 90,player.spaceshipColor);
}

void shoot(Bullet& bullet, SpaceShip player)
{
	bullet.position.x = player.rect.x;
	bullet.position.y = player.rect.y;
	bullet.trayectory = player.normalizedDirection;

	bullet.isActive = true;
	bullet.rotation = player.rotation;
}