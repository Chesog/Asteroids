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
	Rectangle rect;
	float rotation;
	Bullet playerAmmo[playerMaxAmmo];
};

SpaceShip initSpaceShip();
void moveSpaceShip(SpaceShip& player);
void drawPlayer(SpaceShip& player);
void shoot(Bullet& bullet, SpaceShip player);