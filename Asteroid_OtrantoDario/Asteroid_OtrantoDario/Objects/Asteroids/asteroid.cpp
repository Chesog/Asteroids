#include "asteroid.h"

Asteroid initAsteroid(int size, Texture2D asteroidTexture, Texture2D asteroidTextureEvil)
{
	Asteroid aux;
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	aux.position.x = static_cast<float>(GetRandomValue(0, screenWidth));
	if (aux.position.x != 0 || aux.position.x != screenWidth)
	{
		int rand = GetRandomValue(0,2);
		if (rand == 0)
		{
			aux.position.y = 0;
		}
		else if (rand == 1)
		{
			aux.position.y = static_cast<float>(screenHeight);
		}
	}
	if (aux.position.x == 0 || aux.position.x == screenWidth)
	{
		aux.position.x = static_cast<float>(GetRandomValue(0, screenHeight));
	}
	aux.direction.x = static_cast<float>(GetRandomValue(static_cast<int>(Directions::Left), static_cast<int>(Directions::Right)));
	aux.direction.y = static_cast<float>(GetRandomValue(static_cast<int>(Directions::Up), static_cast<int>(Directions::Down)));
	aux.color = DARKGREEN;
	aux.size = static_cast<float>(size);
	aux.rotation = 0;
	aux.asteroidTexture = asteroidTexture;
	aux.asteroidTextureEvil = asteroidTextureEvil;

	if (aux.size == (int)AsteroidSize::Small)
	{
		aux.isActive = false;
		aux.speed = { 200.0f,200.0f };
		aux.radius = 10;
	}
	else if (aux.size == (int)AsteroidSize::Medium)
	{
		aux.isActive = false;
		aux.speed = { 150.0f,150.0f };
		aux.radius = 20;
	}
	else
	{
		aux.isActive = true;
		aux.speed = { 50.0f,50.0f };
		aux.radius = 40;
	}

	return aux;
}

void moveAsteroid(Asteroid& currenAsteroid)
{
	if (currenAsteroid.direction.x == static_cast<int>(Directions::Left))
	{
		currenAsteroid.position.x = currenAsteroid.position.x - currenAsteroid.speed.x * GetFrameTime();
	}
	if (currenAsteroid.direction.x == static_cast<int>(Directions::Right))
	{
		currenAsteroid.position.x = currenAsteroid.position.x + currenAsteroid.speed.x * GetFrameTime();
	}
	if (currenAsteroid.direction.y == static_cast<int>(Directions::Up))
	{
		currenAsteroid.position.y = currenAsteroid.position.y + currenAsteroid.speed.y * GetFrameTime();
	}
	if (currenAsteroid.direction.y == static_cast<int>(Directions::Down))
	{
		currenAsteroid.position.y = currenAsteroid.position.y - currenAsteroid.speed.y * GetFrameTime();
	}

	if (currenAsteroid.direction.x == static_cast<int>(Directions::Left))
	{
		currenAsteroid.rotation = currenAsteroid.rotation - 40.0f * GetFrameTime();
	}
	else
	{
		currenAsteroid.rotation = currenAsteroid.rotation + 40.0f * GetFrameTime();
	}
}
void drawAsteroid(Asteroid currenAsteroid, bool changeCondition)
{
#if _DEBUG
	DrawCircle(static_cast<int>(currenAsteroid.position.x), static_cast<int>(currenAsteroid.position.y), currenAsteroid.radius, currenAsteroid.color);
#endif // _DEBUG
	float scale = 0;

	if (currenAsteroid.size == static_cast<int>(AsteroidSize::Large))
	{
		scale = 2.0f;
	}
	else if (currenAsteroid.size == static_cast<int>(AsteroidSize::Medium))
	{
		scale = 1.5f;
	}
	else
	{
		scale = 1.0f;
	}

	Rectangle sourRect = { 0,0,static_cast<float>(currenAsteroid.asteroidTexture.width),static_cast<float>(currenAsteroid.asteroidTexture.height)};
	Rectangle destRect = { currenAsteroid.position.x,currenAsteroid.position.y,static_cast<float>(currenAsteroid.asteroidTexture.width * scale),static_cast<float>(currenAsteroid.asteroidTexture.height * scale)};
	Vector2 texturePiv = { static_cast<float>((currenAsteroid.asteroidTexture.width * scale) / 2),static_cast<float>((currenAsteroid.asteroidTexture.height * scale) / 2) };

	
	Vector2 texturePos;
	texturePos.x = currenAsteroid.position.x  - currenAsteroid.asteroidTexture.width / 2;
	texturePos.y = currenAsteroid.position.y  - currenAsteroid.asteroidTexture.height / 2;


	if (changeCondition)
	{
		DrawTexturePro(currenAsteroid.asteroidTextureEvil, sourRect, destRect, texturePiv, currenAsteroid.rotation, WHITE);
	}
	else
	{
		DrawTexturePro(currenAsteroid.asteroidTexture, sourRect, destRect, texturePiv, currenAsteroid.rotation, WHITE);
	}
}