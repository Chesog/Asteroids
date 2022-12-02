#include "spaceship.h"
#include <iostream>

namespace cheso_Asteroids
{

	Sound shotSound;
	Sound deadSpaceshipSound;

	static Rectangle sourRect;
	static Rectangle destRect;
	static Vector2 texturePiv;

	extern float animationCounter;
	extern float shootanimationCounter;

	Texture2D spaceShipAcelerationAnim;
	Texture2D spaceshipShotAnim;

	SpaceShip initSpaceShip(Texture2D spaceshipTexture, Texture2D bulletTexture)
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
		aux.isShooting = false;
		aux.isMoving = false;
		aux.spaceshipColor = WHITE;
		aux.speed = 400.0f;
		sourRect = { 0.0f,0.0f,static_cast<float>(aux.spaceshipTexture.width),static_cast<float>(aux.spaceshipTexture.height) };
		for (int i = 0; i < playerMaxAmmo; i++)
		{
			initBullet(aux.playerAmmo[i], bulletTexture);
		}
		return aux;
	}

	void moveSpaceShip(SpaceShip& player)
	{
		player.rect.x = player.rect.x + player.acceleration.x * GetFrameTime();
		player.rect.y = player.rect.y + player.acceleration.y * GetFrameTime();
	}
	void drawPlayer(SpaceShip& player)
	{
#if _DEBUG
		//DrawCircle(static_cast<int>(player.rect.x), static_cast<int>(player.rect.y),player.rad,GREEN);
#endif // _DEBUG

		if (player.isHit)
		{
			int rand = GetRandomValue(0, 2);
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

		int aux = 0;

		if (player.isShooting)
		{
			aux = static_cast<int>(shootanimationCounter);
			sourRect = { 0.0f + (aux * static_cast<int>(spaceshipShotAnim.width / 10)),0.0f,static_cast<float>(spaceshipShotAnim.width / 10),static_cast<float>(spaceshipShotAnim.height) };
			destRect = { player.rect.x,player.rect.y,sourRect.width,sourRect.height };
			texturePiv = { static_cast<float>(spaceshipShotAnim.width / 20),static_cast<float>(spaceshipShotAnim.height / 2) };

			DrawTexturePro(spaceshipShotAnim, sourRect, destRect, texturePiv, player.rotation + 90, player.spaceshipColor);
		}
		else
		{
			aux = static_cast<int>(animationCounter);
			sourRect = { 0.0f + (aux * static_cast<int>(spaceShipAcelerationAnim.width / 11)),0.0f,static_cast<float>(spaceShipAcelerationAnim.width / 11),static_cast<float>(spaceShipAcelerationAnim.height) };
			destRect = { player.rect.x,player.rect.y,sourRect.width,sourRect.height };
			texturePiv = { static_cast<float>(spaceShipAcelerationAnim.width / 22),static_cast<float>(spaceShipAcelerationAnim.height / 2) };

			DrawTexturePro(spaceShipAcelerationAnim, sourRect, destRect, texturePiv, player.rotation + 90, player.spaceshipColor);
		}
	}
	void shoot(Bullet& bullet, SpaceShip player)
	{
		PlaySound(shotSound);

		bullet.position.x = player.rect.x;
		bullet.position.y = player.rect.y;
		bullet.trayectory = player.normalizedDirection;

		bullet.isActive = true;
		bullet.rotation = player.rotation;
	}
	void playerDead()
	{
		PlaySound(deadSpaceshipSound);
	}
}