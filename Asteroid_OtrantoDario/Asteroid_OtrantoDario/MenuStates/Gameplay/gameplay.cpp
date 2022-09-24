#include "gameplay.h"
#include <iostream>

void drawGameplay(SpaceShip player);
void updateGameplay(SpaceShip& player);
void checkInput(SpaceShip& player);
void checkOutOfBounds(SpaceShip& player);

int gameplayLoop(bool& initGame) 
{
	static SpaceShip player;
	if (initGame)
	{
		player = initSpaceShip();
		initGame = false;
	}

	checkInput(player);
	updateGameplay(player);
	drawGameplay(player);

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

	Vector2 normalizedDirection;
	normalizedDirection = Vector2Normalize(distanceDiff);

	if (IsCursorOnScreen())
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		{
			normalizedDirection = Vector2Normalize(distanceDiff);

			player.acceleration.x += normalizedDirection.x;
			player.acceleration.y += normalizedDirection.y;
		}
		if (IsKeyPressed(KEY_SPACE))
		{
			for (int i = 0; i < playerMaxAmmo; i++)
			{
				if (!player.playerAmmo[i].isActive)
				{
					shoot(player.playerAmmo[i],player,normalizedDirection);
#if _DEBUG
					std::cout << "Shoot" << std::endl;
#endif // _DEBUG
				}
			}
		}
	}

}
void drawGameplay(SpaceShip player)
{
	BeginDrawing();

	ClearBackground(BLACK);
	drawPlayer(player);
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			drawBullet(player.playerAmmo[i]);
		}
	}

	EndDrawing();
}
void updateGameplay(SpaceShip& player) 
{
	moveSpaceShip(player);
	checkOutOfBounds(player);

#if _DEBUG
	//std::cout << player.acceleration.x << " --- " << player.acceleration.y << std::endl;
#endif // _DEBUG

	
}
void checkOutOfBounds(SpaceShip& player)
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
}