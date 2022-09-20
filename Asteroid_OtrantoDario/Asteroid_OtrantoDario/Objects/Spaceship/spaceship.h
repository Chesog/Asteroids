#pragma once
#include "raylib.h"
#include "raymath.h"
#include "../Asteroid_OtrantoDario/MenuStates/GlobalEnums/genera_func.h"

struct SpaceShip
{
	int lives;
	int score;
	Vector2 piv;
	Vector2 acceleration;
	Rectangle rect;
	float rotation;
};

SpaceShip initSpaceShip();
void moveSpaceShip(SpaceShip& player);
void drawPlayer(SpaceShip& player);
void shoot();