#include "gameplay.h"
#include <iostream>

void drawGameplay(SpaceShip player, Asteroid largeAsteroids[maxLargeAsteroids], Asteroid medimunAsteroids[maxMediumndAsteroids], Asteroid smallAsteroids[maxSmallAsteroids]);
void updateGameplay(SpaceShip& player);
void checkInput(SpaceShip& player);
void checkOutOfBounds(SpaceShip& player, Bullet playerAmmo[playerMaxAmmo]);



int gameplayLoop(bool& initGame) 
{
	static SpaceShip player;
	static Asteroid largeAsteroids[maxLargeAsteroids];
	static Asteroid medimunAsteroids[maxMediumndAsteroids];
	static Asteroid smallAsteroids[maxSmallAsteroids];

	if (initGame)
	{
		player = initSpaceShip();

		for (int i = 0; i < maxLargeAsteroids; i++)
		{
			largeAsteroids[i] = initAsteroid((int)AsteroidSize::Large);
		}
		for (int i = 0; i < maxMediumndAsteroids; i++)
		{
			medimunAsteroids[i] = initAsteroid((int)AsteroidSize::Medium);
		}
		for (int i = 0; i < maxSmallAsteroids; i++)
		{
			smallAsteroids[i] = initAsteroid((int)AsteroidSize::Small);
		}
		initGame = false;
	}

	checkInput(player);
	updateGameplay(player);
	drawGameplay(player,largeAsteroids,medimunAsteroids,smallAsteroids);

	return (int)MenuStates::Gameplay;
}
void checkInput(SpaceShip& player)
{
	Vector2 distanceDiff;

	distanceDiff.x = GetMouseX() - player.rect.x;
	distanceDiff.y = GetMouseY() - player.rect.y;
	float maxSpeed = 200.0f;
	float angle = atan(distanceDiff.y / distanceDiff.x);
	angle = angle * 180 / PI;
	
	player.rotation = angle;

	player.normalizedDirection = Vector2Normalize(distanceDiff);

	if (IsCursorOnScreen())
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			player.acceleration.x += player.normalizedDirection.x;
			player.acceleration.y += player.normalizedDirection.y;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			for (int i = 0; i < playerMaxAmmo; i++)
			{
				if (!player.playerAmmo[i].isActive)
				{
					shoot(player.playerAmmo[i],player);
#if _DEBUG
					std::cout << " Shoot " <<  i << std::endl;
#endif // _DEBUG
					break;
				}
			}
		}
	}

}
void drawGameplay(SpaceShip player, Asteroid largeAsteroids[maxLargeAsteroids],Asteroid medimunAsteroids[maxMediumndAsteroids],Asteroid smallAsteroids[maxSmallAsteroids])
{
	BeginDrawing();

	ClearBackground(BLACK);
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			drawBullet(player.playerAmmo[i]);
		}
	}
	drawPlayer(player);
	for (int i = 0; i < maxLargeAsteroids; i++)
	{
		drawAsteroid(medimunAsteroids[i]);
	}
	for (int i = 0; i < maxMediumndAsteroids; i++)
	{
		drawAsteroid(largeAsteroids[i]);
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		drawAsteroid(smallAsteroids[i]);
	}
	EndDrawing();
}
void updateGameplay(SpaceShip& player) 
{
	moveSpaceShip(player);
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			moveBullet(player.playerAmmo[i]);
		}
	}
	checkOutOfBounds(player,player.playerAmmo);

#if _DEBUG
	//std::cout << player.acceleration.x << " --- " << player.acceleration.y << std::endl;
#endif // _DEBUG

	
}
void checkOutOfBounds(SpaceShip& player,Bullet playerAmmo[playerMaxAmmo])
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();

	if (player.rect.x < 0)
	{
		player.rect.x = screenWidth;
	}
	if (player.rect.x > screenWidth)
	{
		player.rect.x = 0;
	}
	if (player.rect.y < 0)
	{
		player.rect.y = screenHeight;
	}
	if (player.rect.y > screenHeight)
	{
		player.rect.y = 0;
	}
	
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].position.x < 0)
		{
			player.playerAmmo[i].position.x = player.rect.x;
			player.playerAmmo[i].isActive = false;
			player.playerAmmo[i].trayectory = {0,0};
		}
		if (player.playerAmmo[i].position.x > screenWidth)
		{
			player.playerAmmo[i].position.x = player.rect.x;
			player.playerAmmo[i].isActive = false;
			player.playerAmmo[i].trayectory = { 0,0 };
		}
		if (player.playerAmmo[i].position.y < 0)
		{
			player.playerAmmo[i].position.y = player.rect.y;
			player.playerAmmo[i].isActive = false;
			player.playerAmmo[i].trayectory = { 0,0 };
		}
		if (player.playerAmmo[i].position.y > screenHeight)
		{
			player.playerAmmo[i].position.y = player.rect.y;
			player.playerAmmo[i].isActive = false;
			player.playerAmmo[i].trayectory = { 0,0 };
		}
	}
}