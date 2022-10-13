#pragma once
#include "raylib.h"

namespace cheso_Asteroids
{
	enum class PowerUpType { Penetration, shield };

	struct powerUp
	{
		float powerUpSpawnTimer;
		float powerUpActiveTimer;
		float rad;

		bool isActive;
		bool isAlive;

		int powerUptipe;

		Vector2 position;

		Color powerUpColor;
	};

	powerUp initPowerUp();
	void drawPowerUp(powerUp actualPowerUp);
}