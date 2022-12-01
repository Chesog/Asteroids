#pragma once
#include "raylib.h"
#include "raymath.h"
#include "MenuStates/GlobalEnums/genera_func.h"
#include "Objects/Bullet/bullet.h"

namespace cheso_Asteroids
{
	const int playerMaxAmmo = 100;

	struct SpaceShip
	{
		int lives;
		int score;

		float rad;
		float rotation;
		float speed;

		bool isHit;
		bool isShooting;
		bool isMoving;

		Vector2 piv;
		Vector2 acceleration;
		Vector2 normalizedDirection;

		Rectangle rect;

		Bullet playerAmmo[playerMaxAmmo];

		Color spaceshipColor;

		Texture2D spaceshipTexture;

	};

	SpaceShip initSpaceShip(Texture2D spaceshipTexture, Texture2D bulletTexture);
	void moveSpaceShip(SpaceShip& player);
	void drawPlayer(SpaceShip& player);
	void shoot(Bullet& bullet, SpaceShip player);
	void playerDead();
}