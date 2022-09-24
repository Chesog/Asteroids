#pragma once
#include "raylib.h"

enum class AsteroidSize {Small,Medium,Large};

struct Asteroid
{
	Vector2 position;
	Vector2 speed;
	float size;
	float radius;
	Color color;
};