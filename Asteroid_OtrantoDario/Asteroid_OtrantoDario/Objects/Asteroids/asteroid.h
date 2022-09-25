#pragma once
#include "raylib.h"
#include "../Asteroid_OtrantoDario/MenuStates/GlobalEnums/genera_func.h"

enum class AsteroidSize { Small, Medium, Large };

const int maxLargeAsteroids = 10;
const int maxMediumndAsteroids = 20;
const int maxSmallAsteroids = 40;

struct Asteroid
{
	Vector2 position;
	Vector2 speed;
	Vector2 direction;
	float size;
	float radius;
	Color color;
};

Asteroid initAsteroid(int size);
void moveAsteroid(Asteroid& currenAsteroid);
void drawAsteroid(Asteroid currenAsteroid);