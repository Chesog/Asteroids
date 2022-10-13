#pragma once
#include "raylib.h"
#include "MenuStates/GlobalEnums/genera_func.h"

namespace cheso_Asteroids
{

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
		bool isHit;
		Color color;
		Texture2D asteroidTexture;
		Texture2D asteroidTextureEvil;
	};

	Asteroid initAsteroid(int size, Texture2D asteroidTexture, Texture2D asteroidTextureEvil);
	void moveAsteroid(Asteroid& currenAsteroid);
	void drawAsteroid(Asteroid currenAsteroid, bool changeCondition);
	void asteroidDeadAnimation(Asteroid& currenAsteroid);
}