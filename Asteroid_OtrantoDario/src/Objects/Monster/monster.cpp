#include "monster.h"
#include <iostream>

Monster initMonster(Texture2D monsterTexture)
{
	Monster aux;

	aux.speed = { 1.0f,1.0f };
	aux.lives = 3;
	aux.monsterColor = WHITE;
	aux.rad = 40.0f;
	aux.rect.x = static_cast<float>(GetRandomValue(0, GetScreenWidth()));;
	if (aux.rect.x != 0 || aux.rect.x != GetScreenWidth())
	{
		int rand = GetRandomValue(0, 2);
		if (rand == 0)
		{
			aux.rect.y = 0;
		}
		else if (rand == 1)
		{
			aux.rect.y = static_cast<float>(GetScreenWidth());
		}
	}
	else if (aux.rect.x == 0 || aux.rect.x == GetScreenWidth())
	{
		aux.rect.x = static_cast<float>(GetRandomValue(0, GetScreenWidth()));
	}
	aux.rect.width = aux.rad;
	aux.rect.height = aux.rad;
	aux.piv.x = aux.rect.width / 2;
	aux.piv.y = aux.rect.height / 2;
	aux.rotation = 0.0f;
	aux.trayectory = { 0.0f,0.0f };
	aux.attakTimer = 3.0f;
	aux.lockTimer = 1.5f;
	aux.respawnTimer = 3.0f;
	aux.monsterTexture = monsterTexture;
	aux.isAlive = false;
	aux.isHit = false;
	aux.hitTimer = 3.0f;

	return aux;
}
void moveMonster(Monster& currentMonster, Vector2 target)
{
	currentMonster.trayectory = target;
	if (currentMonster.isAlive)
	{
		std::cout << "Lock on Timer : " << currentMonster.lockTimer << std::endl;
		currentMonster.lockTimer -= GetFrameTime();

		currentMonster.rotation += 200.0f * GetFrameTime();

		if (currentMonster.lockTimer <= 0)
		{
			currentMonster.lockTimer = 0;
			currentMonster.rotation += 400.0f * GetFrameTime();

			currentMonster.rect.x = currentMonster.rect.x + currentMonster.trayectory.x * currentMonster.speed.x * GetFrameTime();
			currentMonster.rect.y = currentMonster.rect.y + currentMonster.trayectory.y * currentMonster.speed.y * GetFrameTime();

			currentMonster.attakTimer -= GetFrameTime();
			if (currentMonster.attakTimer <= 0)
			{
				currentMonster.lockTimer = 1.5f;
				currentMonster.attakTimer = 3.0f;
			}
		}
	}
}
void reciveDamage(Monster& currentMonster)
{
	currentMonster.lives--;
	if (currentMonster.lives <= 0)
	{
		currentMonster.isAlive = false;
		currentMonster.lives = 3;
		currentMonster.respawnTimer = 3.0f;
	}
}
void drawMonster(Monster& currentMonster)
{
#if _DEBUG
	DrawCircle(static_cast<int>(currentMonster.rect.x), static_cast<int>(currentMonster.rect.y), currentMonster.rad, GREEN);
#endif // _DEBUG

	float scale = 1.5f;

	Rectangle sourRect = { 0,0,static_cast<float>(currentMonster.monsterTexture.width),static_cast<float>(currentMonster.monsterTexture.height) };
	Rectangle destRect = { currentMonster.rect.x,currentMonster.rect.y,static_cast<float>(currentMonster.monsterTexture.width * scale),static_cast<float>(currentMonster.monsterTexture.height * scale) };
	Vector2 texturePiv = { static_cast<float>((currentMonster.monsterTexture.width * scale) / 2),static_cast<float>((currentMonster.monsterTexture.height * scale) / 2) };

	if (currentMonster.isHit)
	{
		int rand = GetRandomValue(0, 2);
		if (rand == 0)
		{
			currentMonster.monsterColor.a = 100;
		}
		else
		{
			currentMonster.monsterColor.a = 250;
		}

		
	}
	if (!currentMonster.isHit)
	{
		currentMonster.monsterColor.a = 255;
	}

	DrawTexturePro(currentMonster.monsterTexture, sourRect, destRect, texturePiv, currentMonster.rotation, currentMonster.monsterColor);
}