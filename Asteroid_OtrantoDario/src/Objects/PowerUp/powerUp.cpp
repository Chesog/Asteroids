#include "powerUp.h"
#include <iostream>

namespace cheso_Asteroids
{
	powerUp initPowerUp()
	{
		powerUp aux;
		aux.isActive = false;
		aux.isAlive = true;
		aux.powerUpSpawnTimer = 20.0f;
		aux.powerUpActiveTimer = 5.0f;
		aux.powerUptipe = GetRandomValue(static_cast<int>(PowerUpType::Penetration), static_cast<int>(PowerUpType::shield));
		aux.rad = 20.0f;
		aux.position.x = static_cast<float>(GetRandomValue(static_cast<int>(aux.rad),GetScreenWidth() - static_cast<int>(aux.rad)));
		aux.position.y = static_cast<float>(GetRandomValue(static_cast<int>(aux.rad),GetScreenHeight() - static_cast<int>(aux.rad)));

		if (aux.powerUptipe == static_cast<int>(PowerUpType::Penetration))
		{
			aux.powerUpColor = RED;
		}
		else
		{
			aux.powerUpColor = BLUE;
		}

		std::cout << "Tipo de PowerUp : " << GetRandomValue(static_cast<int>(PowerUpType::Penetration), static_cast<int>(PowerUpType::shield) + 1) << std::endl;
		return aux;
	}
	void drawPowerUp(powerUp actualPowerUp)
	{
		if (actualPowerUp.isAlive)
		{
			DrawCircle(static_cast<int>(actualPowerUp.position.x), static_cast<int>(actualPowerUp.position.y), actualPowerUp.rad, actualPowerUp.powerUpColor);
		}
	}
}