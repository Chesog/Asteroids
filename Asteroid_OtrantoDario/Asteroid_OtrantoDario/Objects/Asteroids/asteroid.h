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
	float rotation;
	bool isActive;
	Color color;
	Texture2D asteroidTexture;
};

Asteroid initAsteroid(int size,Texture2D asteroidTexture);
void moveAsteroid(Asteroid& currenAsteroid);
void drawAsteroid(Asteroid currenAsteroid);