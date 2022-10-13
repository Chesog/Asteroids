#pragma once
#include "raylib.h"
#include "raymath.h"

namespace cheso_Asteroids
{
	struct Bullet
	{
		Vector2 position;
		Vector2 trayectory;
		Vector2 speed;
		float rad;
		float rotation;
		bool isActive;
		Color color;
		Texture2D bulletTexture;
	};
	void initBullet(Bullet& currentBullet, Texture2D bulletTexture);
	void drawBullet(Bullet bullet);
	void moveBullet(Bullet& bullet);
}