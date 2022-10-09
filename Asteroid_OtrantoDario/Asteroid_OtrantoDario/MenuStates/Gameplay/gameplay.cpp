#include "gameplay.h"
#include <iostream>

static SpaceShip player;

static Asteroid largeAsteroids[maxLargeAsteroids];
static Asteroid mediumAsteroids[maxMediumndAsteroids];
static Asteroid smallAsteroids[maxSmallAsteroids];

static Button pauseButton;

extern Texture2D spaceShipTexture;
extern Texture2D bulletTexture;

extern Texture2D largeAsteroidTexture;
extern Texture2D largeAsteroidTextureEvil;

extern Texture2D mediumAsteroidTexture;
extern Texture2D mediumAsteroidTextureEvil;

extern Texture2D smallAsteroidTexture;
extern Texture2D smallAsteroidTextureEvil;


extern Texture2D gameplay_Background;
extern Texture2D gameplay_Background2;

extern float timer;

static int largeAsteroidCount;
static int mediumAsteroidCount;
static int smallAsteroidCount;

static bool pauseGameplay;
static bool change;



void initGameplay(bool& initGame);
void drawGameplay(int changeCondition);
void updateGameplay();
void checkInput();
void checkOutOfBounds();
void checkPlayerOutOfBounds(int screenWidth, int screenHeight);
void checkBulletOutOfBounds(int screenWidth, int screenHeight);
void checkAsteroidsOutOfBounds(int screenWidth, int screenHeight);
void checkColitions();
void bulletAsteroidColition(Bullet& currentBullet, Asteroid& currentAsteroid);
void asteroidOnAsteroidColition(Asteroid& currentAsteroid, Asteroid& currentAsteroid1);
void spaceshipAsteroidColition(Asteroid& currentAsteroid);
void resetAsteroids();
void mouseButtonColition();


int gameplayLoop(bool& initGame, bool& backToMenu)
{
	//Button pauseButton;
	const int changeCondition = 50;

	if (initGame)
	{
		initGameplay(initGame);
		backToMenu = false;
	}

	checkInput();
	if (!pauseGameplay)
	{
		updateGameplay();
	}
	drawGameplay(changeCondition);
	mouseButtonColition();
	if (player.score >= changeCondition)
	{
		change = true;
	}
	else
	{
		change = false;
	}

	if (pauseGameplay)
	{
		if (IsKeyReleased(KEY_ESCAPE))
		{
			return static_cast<int>(MenuStates::MainMenu);
		}
		else
		{
			return static_cast<int>(MenuStates::Gameplay);
		}
	}
	else
	{
		return static_cast<int>(MenuStates::Gameplay);
	}
}
void initGameplay(bool& initGame)
{
	player = initSpaceShip(spaceShipTexture, bulletTexture);

	for (int i = 0; i < maxLargeAsteroids; i++)
	{
		largeAsteroids[i] = initAsteroid((int)AsteroidSize::Large, largeAsteroidTexture, largeAsteroidTextureEvil);
	}
	for (int i = 0; i < maxMediumndAsteroids; i++)
	{
		mediumAsteroids[i] = initAsteroid((int)AsteroidSize::Medium, mediumAsteroidTexture, mediumAsteroidTextureEvil);
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		smallAsteroids[i] = initAsteroid((int)AsteroidSize::Small, smallAsteroidTexture, smallAsteroidTextureEvil);
	}
	largeAsteroidCount = maxLargeAsteroids;
	mediumAsteroidCount = 0;
	smallAsteroidCount = 0;

	int buttonWidth = 100;
	int buttonHeight = 20;
	pauseButton = initButton((GetScreenWidth() / 2) - (buttonWidth / 2), buttonHeight / 2, 10, buttonWidth, buttonHeight, 14, "Pause", GREEN, RED);
	pauseGameplay = true;
	initGame = false;

}
void checkInput()
{
	if (IsKeyPressed(KEY_SPACE))
	{
		if (pauseGameplay)
		{
			pauseGameplay = false;
		}
		else
		{
			pauseGameplay = true;
		}
	}
	if (!pauseGameplay)
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
			if (!player.isHit)
			{
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
	}
}
void drawGameplay(int changeCondition)
{
	Vector2 backgroundPosition = { 0.0f,0.0f };

	BeginDrawing();
	if (player.score < changeCondition)
	{
		DrawTextureEx(gameplay_Background, backgroundPosition, 0, 1.5f, WHITE);
	}
	else
	{
		DrawTextureEx(gameplay_Background2, backgroundPosition, 0, 1.5f, WHITE);
	}

	if (player.lives == 3)
	{
		DrawTexture(spaceShipTexture, GetScreenWidth() - spaceShipTexture.width * 2, spaceShipTexture.height / 2, WHITE);
		DrawTexture(spaceShipTexture, GetScreenWidth() - spaceShipTexture.width * 3, spaceShipTexture.height / 2, WHITE);
		DrawTexture(spaceShipTexture, GetScreenWidth() - spaceShipTexture.width * 4, spaceShipTexture.height / 2, WHITE);
	}
	else if (player.lives == 2)
	{
		DrawTexture(spaceShipTexture, GetScreenWidth() - spaceShipTexture.width * 3, spaceShipTexture.height / 2, WHITE);
		DrawTexture(spaceShipTexture, GetScreenWidth() - spaceShipTexture.width * 4, spaceShipTexture.height / 2, WHITE);
	}
	else if (player.lives == 1)
	{
		DrawTexture(spaceShipTexture, GetScreenWidth() - spaceShipTexture.width * 4, spaceShipTexture.height / 2, WHITE);
	}
	DrawRectangle(2, 2, 200, 30, GREEN);
	drawButton(pauseButton);
	DrawText(TextFormat("Player Score: %i", player.score), 6, 6, 20, RED);


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
			drawAsteroid(largeAsteroids[i], change);
		}
	}
	for (int i = 0; i < maxMediumndAsteroids; i++)
	{
		if (mediumAsteroids[i].isActive)
		{
			drawAsteroid(mediumAsteroids[i], change);
		}
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		if (smallAsteroids[i].isActive)
		{
			drawAsteroid(smallAsteroids[i], change);
		}
	}

	if (pauseGameplay)
	{
		DrawRectangle((GetScreenWidth() / 2) - 200, (GetScreenHeight() / 2) - 100, 400, 200, BLACK);
	}

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

	if (player.isHit)
	{
		timer += GetFrameTime();
		if (timer >= 3)
		{
			player.isHit = false;
			timer = 0;
		}
	}

	checkOutOfBounds();
	checkColitions();
	resetAsteroids();

	if (player.lives <= 0)
	{
		pauseGameplay = true;
	}

	std::cout << "Timer : " << timer << endl;

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

	for (int i = 0; i < maxLargeAsteroids; i++)
	{
		for (int j = 0; j < maxMediumndAsteroids; j++)
		{
			for (int h = 0; h < maxSmallAsteroids; h++)
			{
				if (largeAsteroids[i].isActive && mediumAsteroids[j].isActive)
				{
					asteroidOnAsteroidColition(largeAsteroids[i], mediumAsteroids[j]);
				}
				if (mediumAsteroids[j].isActive && smallAsteroids[h].isActive)
				{
					asteroidOnAsteroidColition(mediumAsteroids[j], smallAsteroids[h]);
				}
				if (largeAsteroids[i].isActive && smallAsteroids[h].isActive)
				{
					asteroidOnAsteroidColition(largeAsteroids[i], smallAsteroids[h]);
				}
			}
		}

	}

	for (int i = 0; i < maxLargeAsteroids; i++)
	{
		if (largeAsteroids[i].isActive)
		{
			spaceshipAsteroidColition(largeAsteroids[i]);
		}
	}

	for (int i = 0; i < maxMediumndAsteroids; i++)
	{
		if (mediumAsteroids[i].isActive)
		{
			spaceshipAsteroidColition(mediumAsteroids[i]);
		}
	}

	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		if (smallAsteroids[i].isActive)
		{
			spaceshipAsteroidColition(smallAsteroids[i]);
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

			mediumAsteroids[mediumAsteroidCount].direction.x = static_cast<float>(GetRandomValue(0, 2));
			mediumAsteroids[mediumAsteroidCount].direction.y = static_cast<float>(GetRandomValue(2, 4));
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
		if (currentAsteroid.size == static_cast<int>(AsteroidSize::Medium))
		{
			currentAsteroid.isActive = false;
			currentBullet.isActive = false;

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
void asteroidOnAsteroidColition(Asteroid& currentAsteroid, Asteroid& currentAsteroid1)
{
	float distanceX = 0;
	float distanceY = 0;
	float distance = 0;

	distanceX = currentAsteroid.position.x - currentAsteroid1.position.x;
	distanceY = currentAsteroid.position.y - currentAsteroid1.position.y;

	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance < currentAsteroid1.radius + currentAsteroid.radius)
	{
		if (currentAsteroid.direction.x == static_cast<int>(Directions::Left))
		{
			currentAsteroid.direction.x = static_cast<int>(Directions::Right);
		}
		else
		{
			currentAsteroid.direction.x = static_cast<int>(Directions::Left);
		}

		if (currentAsteroid.direction.y == static_cast<int>(Directions::Up))
		{
			currentAsteroid.direction.y = static_cast<int>(Directions::Down);
		}
		else
		{
			currentAsteroid.direction.y = static_cast<int>(Directions::Up);
		}

		if (currentAsteroid1.direction.x == static_cast<int>(Directions::Left))
		{
			currentAsteroid1.direction.x = static_cast<int>(Directions::Right);
		}
		else
		{
			currentAsteroid1.direction.x = static_cast<int>(Directions::Left);
		}

		if (currentAsteroid1.direction.y == static_cast<int>(Directions::Up))
		{
			currentAsteroid1.direction.y = static_cast<int>(Directions::Down);
		}
		else
		{
			currentAsteroid1.direction.y = static_cast<int>(Directions::Up);
		}
	}
}
void spaceshipAsteroidColition(Asteroid& currentAsteroid)
{
	float distanceX = 0;
	float distanceY = 0;
	float distance = 0;

	distanceX = currentAsteroid.position.x - player.rect.x;
	distanceY = currentAsteroid.position.y - player.rect.y;

	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance < player.rad + currentAsteroid.radius)
	{
		if (!player.isHit)
		{
			currentAsteroid.isActive = false;
			player.lives--;
			player.acceleration.y = player.acceleration.y * -1.0f;
			player.acceleration.x = player.acceleration.x * -1.0f;

			if (currentAsteroid.size == static_cast<int>(AsteroidSize::Large))
			{
				if (mediumAsteroidCount < maxMediumndAsteroids)
				{
					mediumAsteroids[mediumAsteroidCount].direction.x = static_cast<float>(GetRandomValue(0, 2));
					mediumAsteroids[mediumAsteroidCount].direction.y = static_cast<float>(GetRandomValue(2, 4));
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
			else if (currentAsteroid.size == static_cast<int>(AsteroidSize::Medium))
			{
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
			player.score++;
			player.isHit = true;
		}
	}
}
void resetAsteroids()
{
	int activeAsteroids = 0;
	int minAsteroidsOnScreen = 0;

	for (int i = 0; i < maxLargeAsteroids; i++)
	{
		if (largeAsteroids[i].isActive)
		{
			activeAsteroids++;
		}
	}
	for (int i = 0; i < maxMediumndAsteroids; i++)
	{
		if (mediumAsteroids[i].isActive)
		{
			activeAsteroids++;
		}
	}
	for (int i = 0; i < maxSmallAsteroids; i++)
	{
		if (smallAsteroids[i].isActive)
		{
			activeAsteroids++;
		}
	}

	if (activeAsteroids == minAsteroidsOnScreen)
	{
		for (int i = 0; i < maxLargeAsteroids; i++)
		{
			largeAsteroids[i] = initAsteroid(static_cast<int>(AsteroidSize::Large), largeAsteroidTexture, largeAsteroidTextureEvil);
		}
		for (int i = 0; i < maxMediumndAsteroids; i++)
		{
			mediumAsteroids[i] = initAsteroid(static_cast<int>(AsteroidSize::Medium), mediumAsteroidTexture, mediumAsteroidTextureEvil);
		}
		for (int i = 0; i < maxSmallAsteroids; i++)
		{
			smallAsteroids[i] = initAsteroid(static_cast<int>(AsteroidSize::Small), smallAsteroidTexture, smallAsteroidTextureEvil);
		}
		largeAsteroidCount = maxLargeAsteroids;
		mediumAsteroidCount = 0;
		smallAsteroidCount = 0;
	}
}
void mouseButtonColition()
{
	Vector2 mousePosition = { static_cast<float>(GetMouseX()),static_cast<float>(GetMouseY()) };

	if (CheckCollisionPointRec(mousePosition, pauseButton.rect))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (pauseGameplay)
			{
				pauseGameplay = false;
			}
			else
			{
				pauseGameplay = true;
			}
		}

	}
}