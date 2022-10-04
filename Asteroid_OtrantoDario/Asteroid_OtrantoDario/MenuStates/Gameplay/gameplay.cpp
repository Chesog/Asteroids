#include "gameplay.h"
#include <iostream>

static SpaceShip player;
static Asteroid largeAsteroids[maxLargeAsteroids];
static Asteroid mediumAsteroids[maxMediumndAsteroids];
static Asteroid smallAsteroids[maxSmallAsteroids];

extern Texture2D spaceShipTexture;
extern Texture2D bulletTexture;
extern Texture2D largeAsteroidTexture;

static int largeAsteroidCount;
static int mediumAsteroidCount;
static int smallAsteroidCount;

void initGameplay(bool& initGame);
void drawGameplay();
void updateGameplay();
void checkInput();
void checkOutOfBounds();
void checkPlayerOutOfBounds(int screenWidth, int screenHeight);
void checkBulletOutOfBounds(int screenWidth, int screenHeight);
void checkAsteroidsOutOfBounds(int screenWidth, int screenHeight);
void checkColitions();
void bulletAsteroidColition(Bullet& currentBullet, Asteroid& currentAsteroid);


int gameplayLoop(bool& initGame)
{

	if (initGame)
	{
		initGameplay(initGame);
	}

	checkInput();
	updateGameplay();
	drawGameplay();

	return (int)MenuStates::Gameplay;
}
void initGameplay(bool& initGame)
{


	player = initSpaceShip(spaceShipTexture, bulletTexture);

	for (int i = 0; i < maxLargeAsteroids; i++)
	{
		largeAsteroids[i] = initAsteroid((int)AsteroidSize::Large,largeAsteroidTexture);
	}
	for (int i = 0; i < maxMediumndAsteroids; i++)
	{
		mediumAsteroids[i] = initAsteroid((int)AsteroidSize::Medium, largeAsteroidTexture);
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		smallAsteroids[i] = initAsteroid((int)AsteroidSize::Small,largeAsteroidTexture);
	}
	largeAsteroidCount = maxLargeAsteroids;
	mediumAsteroidCount = 0;
	smallAsteroidCount = 0;
	initGame = false;
}
void checkInput()
{
	Vector2 distanceDiff;

	distanceDiff.x = GetMouseX() - player.rect.x;
	distanceDiff.y = GetMouseY() - player.rect.y;
	float angle = atan(distanceDiff.y / distanceDiff.x);
	angle = angle * 180 / PI;

	if (GetMousePosition().x < player.rect.x && GetMousePosition().y < player.rect.y)
	{
		angle += 180;
	}
	if (GetMousePosition().x < player.rect.x && GetMousePosition().y > player.rect.y)
	{
		angle += 180;
	}
	if (GetMousePosition().x > player.rect.x && GetMousePosition().y > player.rect.y)
	{
		angle += 360;
	}

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
					shoot(player.playerAmmo[i], player);
#if _DEBUG
					std::cout << " Shoot " << i << std::endl;
#endif // _DEBUG
					break;
				}
			}
		}
	}

}
void drawGameplay()
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
		if (largeAsteroids[i].isActive)
		{
			drawAsteroid(largeAsteroids[i]);
		}
	}
	for (int i = 0; i < maxMediumndAsteroids; i++)
	{
		if (mediumAsteroids[i].isActive)
		{
			drawAsteroid(mediumAsteroids[i]);
		}
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		if (smallAsteroids[i].isActive)
		{
			drawAsteroid(smallAsteroids[i]);
		}
	}
	DrawText(TextFormat(" Player Score %i ",player.score),GetScreenWidth() / 2,GetScreenHeight() / 2,20,RED);
	EndDrawing();
}
void updateGameplay()
{
	moveSpaceShip(player);
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			moveBullet(player.playerAmmo[i]);
		}
	}
	for (int i = 0; i < maxLargeAsteroids; i++)
	{
		moveAsteroid(largeAsteroids[i]);
	}
	for (int i = 0; i < maxMediumndAsteroids; i++)
	{
		moveAsteroid(mediumAsteroids[i]);
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		moveAsteroid(smallAsteroids[i]);
	}
	checkOutOfBounds();
	checkColitions();

#if _DEBUG
	//std::cout << player.acceleration.x << " --- " << player.acceleration.y << std::endl;
#endif // _DEBUG


}
void checkOutOfBounds()
{
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();
	checkPlayerOutOfBounds(screenWidth, screenHeight);
	checkBulletOutOfBounds(screenWidth, screenHeight);
	checkAsteroidsOutOfBounds(screenWidth, screenHeight);
}
void checkPlayerOutOfBounds(int screenWidth, int screenHeight)
{
	if (player.rect.x < 0)
	{
		player.rect.x = static_cast<float>(screenWidth);
	}
	if (player.rect.x > static_cast<float>(screenWidth))
	{
		player.rect.x = 0;
	}
	if (player.rect.y < 0)
	{
		player.rect.y = static_cast<float>(screenHeight);
	}
	if (player.rect.y > static_cast<float>(screenHeight))
	{
		player.rect.y = 0;
	}
}
void checkBulletOutOfBounds(int screenWidth, int screenHeight)
{
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].position.x < 0)
		{
			player.playerAmmo[i].position.x = player.rect.x;
			player.playerAmmo[i].isActive = false;
			player.playerAmmo[i].trayectory = { 0,0 };
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
void checkAsteroidsOutOfBounds(int screenWidth, int screenHeight)
{
	for (int i = 0; i < maxLargeAsteroids; i++)
	{
		if (largeAsteroids[i].position.x < 0 - largeAsteroids[i].radius)
		{
			largeAsteroids[i].position.x = static_cast<float>(screenWidth);
		}
		if (largeAsteroids[i].position.x > static_cast<float>(screenWidth) + largeAsteroids[i].radius)
		{
			largeAsteroids[i].position.x = 0;
		}
		if (largeAsteroids[i].position.y < 0 - largeAsteroids[i].radius)
		{
			largeAsteroids[i].position.y = static_cast<float>(screenHeight);
		}
		if (largeAsteroids[i].position.y > static_cast<float>(screenHeight) + largeAsteroids[i].radius)
		{
			largeAsteroids[i].position.y = 0;
		}
	}
	for (int i = 0; i < maxMediumndAsteroids; i++)
	{
		if (mediumAsteroids[i].position.x < 0 - mediumAsteroids[i].radius)
		{
			mediumAsteroids[i].position.x = static_cast<float>(screenWidth);
		}
		if (mediumAsteroids[i].position.x > static_cast<float>(screenWidth) + mediumAsteroids[i].radius)
		{
			mediumAsteroids[i].position.x = 0;
		}
		if (mediumAsteroids[i].position.y < 0 - mediumAsteroids[i].radius)
		{
			mediumAsteroids[i].position.y = static_cast<float>(screenHeight);
		}
		if (mediumAsteroids[i].position.y > static_cast<float>(screenHeight) + mediumAsteroids[i].radius)
		{
			mediumAsteroids[i].position.y = 0;
		}
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		if (smallAsteroids[i].position.x < 0 - smallAsteroids[i].radius)
		{
			smallAsteroids[i].position.x = static_cast<float>(screenWidth);
		}
		if (smallAsteroids[i].position.x > static_cast<float>(screenWidth) + smallAsteroids[i].radius)
		{
			smallAsteroids[i].position.x = 0;
		}
		if (smallAsteroids[i].position.y < 0 - smallAsteroids[i].radius)
		{
			smallAsteroids[i].position.y = static_cast<float>(screenHeight);
		}
		if (smallAsteroids[i].position.y > static_cast<float>(screenHeight) + smallAsteroids[i].radius)
		{
			smallAsteroids[i].position.y = 0;
		}
	}
}
void checkColitions()
{

	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			for (int j = 0; j < maxLargeAsteroids; j++)
			{
				if (largeAsteroids[j].isActive)
				{
					bulletAsteroidColition(player.playerAmmo[i], largeAsteroids[j]);
				}
			}
		}
	}

	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			for (int j = 0; j < maxMediumndAsteroids; j++)
			{
				if (mediumAsteroids[j].isActive)
				{
					bulletAsteroidColition(player.playerAmmo[i], mediumAsteroids[j]);
				}
			}
		}
	}

	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			for (int j = 0; j < maxSmallAsteroids; j++)
			{
				if (smallAsteroids[j].isActive)
				{
					bulletAsteroidColition(player.playerAmmo[i], smallAsteroids[j]);
				}
			}
		}
	}
}
void bulletAsteroidColition(Bullet& currentBullet, Asteroid& currentAsteroid)
{
	float distanceX = 0;
	float distanceY = 0;
	float distance = 0;

	distanceX = currentAsteroid.position.x - currentBullet.position.x;
	distanceY = currentAsteroid.position.y - currentBullet.position.y;

	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));


	if (distance < currentBullet.rad + currentAsteroid.radius)
	{
		if (currentAsteroid.size == static_cast<int>(AsteroidSize::Large))
		{
			currentAsteroid.isActive = false;
			currentBullet.isActive = false;

			if (mediumAsteroidCount < maxMediumndAsteroids)
			{
				mediumAsteroids[mediumAsteroidCount].direction.x = static_cast<float>(GetRandomValue(0,2));
				mediumAsteroids[mediumAsteroidCount].direction.y = static_cast<float>(GetRandomValue(2,4));
				mediumAsteroids[mediumAsteroidCount].position.x = currentAsteroid.position.x;
				mediumAsteroids[mediumAsteroidCount].position.y = currentAsteroid.position.y;
				mediumAsteroids[mediumAsteroidCount].isActive = true;
				mediumAsteroidCount++;

				if (mediumAsteroids[mediumAsteroidCount - 1].direction.x == static_cast<int>(Directions::Left))
				{
					mediumAsteroids[mediumAsteroidCount].direction.x = static_cast<int>(Directions::Right);
				}
				else
				{
					mediumAsteroids[mediumAsteroidCount].direction.x = static_cast<int>(Directions::Left);
				}
				if (mediumAsteroids[mediumAsteroidCount - 1].direction.y == static_cast<int>(Directions::Up))
				{
					mediumAsteroids[mediumAsteroidCount].direction.y = static_cast<int>(Directions::Down);
				}
				else
				{
					mediumAsteroids[mediumAsteroidCount - 1].direction.y = static_cast<int>(Directions::Up);
				}
				mediumAsteroids[mediumAsteroidCount].position.x = currentAsteroid.position.x;
				mediumAsteroids[mediumAsteroidCount].position.y = currentAsteroid.position.y;
				mediumAsteroids[mediumAsteroidCount].isActive = true;
				mediumAsteroidCount++;

				largeAsteroidCount--;
			}
		}
		if (currentAsteroid.size == static_cast<int>(AsteroidSize::Medium))
		{
			currentAsteroid.isActive = false;
			currentBullet.isActive = false;

			if (smallAsteroidCount < maxSmallAsteroids)
			{

				smallAsteroids[smallAsteroidCount].direction.x = static_cast<float>(GetRandomValue(0, 2));
				smallAsteroids[smallAsteroidCount].direction.y = static_cast<float>(GetRandomValue(2, 4));
				smallAsteroids[smallAsteroidCount].position.x = currentAsteroid.position.x;
				smallAsteroids[smallAsteroidCount].position.y = currentAsteroid.position.y;
				smallAsteroids[smallAsteroidCount].isActive = true;
				smallAsteroidCount++;

				if (smallAsteroids[smallAsteroidCount - 1].direction.x == static_cast<int>(Directions::Left))
				{
					smallAsteroids[smallAsteroidCount].direction.x = static_cast<int>(Directions::Right);
				}
				else
				{
					smallAsteroids[smallAsteroidCount].direction.x = static_cast<int>(Directions::Left);
				}
				if (smallAsteroids[smallAsteroidCount - 1].direction.y == static_cast<int>(Directions::Up))
				{
					smallAsteroids[smallAsteroidCount].direction.y = static_cast<int>(Directions::Down);
				}
				else
				{
					smallAsteroids[smallAsteroidCount - 1].direction.y = static_cast<int>(Directions::Up);
				}
				smallAsteroids[smallAsteroidCount].position.x = currentAsteroid.position.x;
				smallAsteroids[smallAsteroidCount].position.y = currentAsteroid.position.y;
				smallAsteroids[smallAsteroidCount].isActive = true;
				smallAsteroidCount++;
			}
		}
		if (currentAsteroid.size == static_cast<int>(AsteroidSize::Small))
		{
			currentAsteroid.isActive = false;
			currentBullet.isActive = false;
		}
		player.score++;
#if _DEBUG
		std::cout << "Meteoritos Grandes" << largeAsteroidCount << std::endl;
		std::cout << "Meteoritos Medianos" << mediumAsteroidCount << std::endl;
		std::cout << "Meteoritos Chicos" << smallAsteroidCount << std::endl;
#endif // _DEBUG
	}
}