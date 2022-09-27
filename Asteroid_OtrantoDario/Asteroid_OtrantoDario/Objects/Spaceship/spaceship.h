#pragma once
#include "raylib.h"
#include "raymath.h"
#include "../Asteroid_OtrantoDario/MenuStates/GlobalEnums/genera_func.h"
#include "../Bullet/bullet.h"

const int playerMaxAmmo = 100;

struct SpaceShip
{
	int lives;
	int score;
	Vector2 piv;
	Vector2 acceleration;
	Vector2 normalizedDirection;
	float rad;
	Rectangle rect;
	float rotation;
	Bullet playerAmmo[playerMaxAmmo];
	Texture2D spaceshipTexture;
};

SpaceShip initSpaceShip(Texture2D spaceshipTexture, Texture2D bulletTexture);
void moveSpaceShip(SpaceShip& player);
void drawPlayer(SpaceShip& player);
void shoot(Bullet& bullet, SpaceShip player);