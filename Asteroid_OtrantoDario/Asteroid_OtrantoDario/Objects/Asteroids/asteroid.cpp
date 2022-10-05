#include "asteroid.h"

Asteroid initAsteroid(int size,Texture2D asteroidTexture)
{
	Asteroid aux;
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	aux.position.x =  static_cast<float>(GetRandomValue(0, screenWidth));
	aux.position.y =  static_cast<float>(GetRandomValue(0, screenHeight));
	aux.direction.x = static_cast<float>(GetRandomValue(static_cast<int>(Directions::Left), static_cast<int>(Directions::Right)));
	aux.direction.y = static_cast<float>(GetRandomValue(static_cast<int>(Directions::Up), static_cast<int>(Directions::Down)));
	aux.color = DARKGREEN;
	aux.size = static_cast<float>(size);
	aux.rotation = 0;
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
void drawAsteroid(Asteroid currenAsteroid)
{
#if _DEBUG
	DrawCircle(static_cast<int>(currenAsteroid.position.x), static_cast<int>(currenAsteroid.position.y), currenAsteroid.radius, currenAsteroid.color);
#endif // _DEBUG

	Rectangle sourRect = { 0,0,static_cast<float>(currenAsteroid.asteroidTexture.width),static_cast<float>(currenAsteroid.asteroidTexture.height)};
	Rectangle destRect = {currenAsteroid.position.x,currenAsteroid.position.y,sourRect.width,sourRect.height};
	Vector2 texturePiv = { static_cast<float>(currenAsteroid.asteroidTexture.width / 2),static_cast<float>(currenAsteroid.asteroidTexture.height / 2)};

	//DrawTextureEx(currenAsteroid.asteroidTexture,currenAsteroid.position,currenAsteroid.rotation,2.0f,WHITE);
	DrawTexturePro(currenAsteroid.asteroidTexture, sourRect, destRect, texturePiv,currenAsteroid.rotation, WHITE);
}