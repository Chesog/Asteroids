#include "asteroid.h"

Asteroid initAsteroid(int size)
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

	if (aux.size == (int)AsteroidSize::Small)
	{
		aux.speed = { 100.0f,100.0f };
		aux.radius = 20;
	}
	else if (aux.size == (int)AsteroidSize::Medium)
	{
		aux.speed = { 150.0f,150.0f };
		aux.radius = 15;
	}
	else
	{
		aux.speed = { 200.0f,200.0f };
		aux.radius = 10;
	}

	return aux;
}

void moveAsteroid(Asteroid currenAsteroid)
{
	if (currenAsteroid.direction.x == (int)Directions::Left)
	{
		currenAsteroid.position.x--;
	}
	if (currenAsteroid.direction.x == (int)Directions::Right)
	{
		currenAsteroid.position.x++;
	}
	if (currenAsteroid.direction.y == (int)Directions::Up)
	{
		currenAsteroid.position.y++;
	}
	if (currenAsteroid.direction.y == (int)Directions::Down)
	{
		currenAsteroid.position.y--;
	}
}
void drawAsteroid(Asteroid currenAsteroid)
{
	DrawCircle(currenAsteroid.position.x, currenAsteroid.position.y, currenAsteroid.radius, currenAsteroid.color);
}