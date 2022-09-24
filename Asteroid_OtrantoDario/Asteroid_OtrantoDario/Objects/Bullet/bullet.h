#pragma once
#include "raylib.h"
#include "raymath.h"

struct Bullet
{
	Vector2 position;
	Vector2 trayectory;
	Vector2 speed;
	float rad;
	float rotation;
	bool isActive;
	Color color;
};

void drawBullet(Bullet bullet);