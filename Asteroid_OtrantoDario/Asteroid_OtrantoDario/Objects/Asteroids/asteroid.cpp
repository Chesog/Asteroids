#include "asteroid.h"

Asteroid initAsteroid(int size,Texture2D asteroidTexture)
{
	Asteroid aux;
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	aux.position.x = GetRandomValue(0, screenWidth);
	aux.position.y = GetRandomValue(0, screenWidth);
	aux.direction.x = GetRandomValue((int)Directions::Left, (int)Directions::Right);
	aux.direction.y = GetRandomValue((int)Directions::Up, (int)Directions::Down);
	aux.color = DARKGREEN;
	aux.size = size;
	aux.asteroidTexture = asteroidTexture;

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
	if (currenAsteroid.direction.x == (int)Directions::Left)
	{
		currenAsteroid.position.x = currenAsteroid.position.x - currenAsteroid.speed.x * GetFrameTime();
	}
	if (currenAsteroid.direction.x == (int)Directions::Right)
	{
		currenAsteroid.position.x = currenAsteroid.position.x + currenAsteroid.speed.x * GetFrameTime();
	}
	if (currenAsteroid.direction.y == (int)Directions::Up)
	{
		currenAsteroid.position.y = currenAsteroid.position.y + currenAsteroid.speed.y * GetFrameTime();
	}
	if (currenAsteroid.direction.y == (int)Directions::Down)
	{
		currenAsteroid.position.y = currenAsteroid.position.y - currenAsteroid.speed.y * GetFrameTime();
	}
}
void drawAsteroid(Asteroid currenAsteroid)
{
#if _DEBUG
	DrawCircle(currenAsteroid.position.x, currenAsteroid.position.y, currenAsteroid.radius, currenAsteroid.color);
#endif // _DEBUG

	Rectangle sourRect = { 0,0,currenAsteroid.asteroidTexture.width,currenAsteroid.asteroidTexture.height};
	Rectangle destRect = {currenAsteroid.position.x,currenAsteroid.position.y,sourRect.width,sourRect.height};
	Vector2 texturePiv = {currenAsteroid.asteroidTexture.width / 2,currenAsteroid.asteroidTexture.height / 2};

	DrawTexturePro(currenAsteroid.asteroidTexture, sourRect, destRect, texturePiv,0 + 90, WHITE);
}