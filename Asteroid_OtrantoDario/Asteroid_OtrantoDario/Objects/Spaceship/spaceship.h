#pragma once
#include "raylib.h"
#include "../Asteroid_OtrantoDario/MenuStates/GlobalEnums/genera_func.h"

struct SpaceShip
{
	float posX;
	float posY;
	int lives;
	int score;
	int currentDirectionX;
	int currentDirectionY;
	Rectangle rect;
};

SpaceShip initSpaceShip();
void moveSpaceShip(SpaceShip& player);
void shoot();