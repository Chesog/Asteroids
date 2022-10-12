#include "gameplay.h"
#include <iostream>

static SpaceShip player;
static Monster monster;

static Asteroid largeAsteroids[maxLargeAsteroids];
static Asteroid mediumAsteroids[maxMediumndAsteroids];
static Asteroid smallAsteroids[maxSmallAsteroids];

static Button pauseButton;
static Button continueButton;
static Button returnButton;
static Button resetButton;

static int largeAsteroidCount;
static int mediumAsteroidCount;
static int smallAsteroidCount;

static bool pauseGameplay;
static bool change;

float animationCounter;
float shootanimationCounter;
//float explosionAnimationCounter;


extern float timer;

extern Texture2D spaceShipAcelerationAnim;
extern Texture2D spaceshipShotAnim;

int highScore;

Music gameplayMusic;

Sound asteroidShotSound;

Texture2D mouseTextureGameplay;

Texture2D spaceShipTexture;
Texture2D bulletTexture;
Texture2D monsterTexture;


Texture2D asteroidexplosionAnim;

Texture2D largeAsteroidTexture;
Texture2D largeAsteroidTextureEvil;

Texture2D mediumAsteroidTexture;
Texture2D mediumAsteroidTextureEvil;

Texture2D smallAsteroidTexture;
Texture2D smallAsteroidTextureEvil;


Texture2D gameplay_Background;
Texture2D gameplay_Background2;

Texture2D pauseMenuTexture;

Texture2D continueTexture;
Texture2D resetTexture;
Texture2D returnTexture;
Texture2D pauseButtonTexture;





void initGameplay(bool& initGame);
void drawGameplay(int changeCondition);
void updateGameplay();
void checkInput();
void checkOutOfBounds();
void checkPlayerOutOfBounds(int screenWidth, int screenHeight);
void checkBulletOutOfBounds(int screenWidth, int screenHeight);
void checkAsteroidsOutOfBounds(int screenWidth, int screenHeight);
void checkMonsterOutOfBounds(int screenWidth, int screenHeight);
void checkColitions();
void bulletAsteroidColition(Bullet& currentBullet, Asteroid& currentAsteroid);
void bulletMonsterColition(Bullet& currentBullet);
void asteroidOnAsteroidColition(Asteroid& currentAsteroid, Asteroid& currentAsteroid1);
void spaceshipAsteroidColition(Asteroid& currentAsteroid);
void spaceshipMonsterColition();
void resetAsteroids();
void mouseButtonColition(bool& initGame, bool& backToMenu);


int gameplayLoop(bool& initGame, bool& backToMenu)
{
	const int changeCondition = 666;

	UpdateMusicStream(gameplayMusic);

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
	mouseButtonColition(initGame, backToMenu);
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
			backToMenu = true;
		}
	}

	if (backToMenu)
	{
		if (SaveStorageValue(0, highScore))
		{
			std::cout << "Se guardo Correctamente";
		}
		return static_cast<int>(MenuStates::MainMenu);
	}
	else
	{
		return static_cast<int>(MenuStates::Gameplay);
	}
}
void initGameplay(bool& initGame)
{
	player = initSpaceShip(spaceShipTexture, bulletTexture);
	monster = initMonster(monsterTexture);
	animationCounter = 0.0f;
	shootanimationCounter = 0.0f;
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

	int buttonWidth = 150;
	int buttonHeight = 40;
	//int pauseHeight = 400;
	int fontSize = 40;


	pauseButton = initButton((GetScreenWidth() / 2) - (buttonWidth / 2), buttonHeight / 2, fontSize, buttonWidth, buttonHeight, 14, "Pause", GREEN, RED);
	continueButton = initButton((GetScreenWidth() / 2) - (buttonWidth / 2), static_cast<int>((GetScreenHeight() / 2) - (buttonHeight * 4.5f)), fontSize, buttonWidth, buttonHeight, 0, "Continue", GREEN, RED);
	resetButton = initButton((GetScreenWidth() / 2) - (buttonWidth / 2), static_cast<int>((GetScreenHeight() / 2) - (buttonHeight * 2.1f)), fontSize, buttonWidth, buttonHeight, 0, "Reset", GREEN, RED);
	returnButton = initButton((GetScreenWidth() / 2) - buttonWidth / 2, static_cast<int>((GetScreenHeight() / 2) + (buttonHeight * 3.6f)), fontSize, buttonWidth, buttonHeight, 0, "Return", GREEN, RED);

	pauseGameplay = true;
	initGame = false;

}
void checkInput()
{
	if (IsKeyPressed(KEY_ESCAPE))
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
				animationCounter += GetFrameTime() * 10;
				if (animationCounter > 10)
				{
					animationCounter = 1;
				}
				player.isMoving = true;
			}
			else
			{
				player.isMoving = false;
				animationCounter = 0;
			}
			cout << "Shoot Animation Counter : " << shootanimationCounter << endl;
			if (!player.isHit)
			{
				if (player.isShooting)
				{
					shootanimationCounter += GetFrameTime() * 60;
				}
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					if (shootanimationCounter == 0)
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
						player.isShooting = true;

					}
				}
				else
				{
					if (shootanimationCounter > 9)
					{
						shootanimationCounter = 0;
						player.isShooting = false;
					}
				}
			}
		}
	}
}
void drawGameplay(int changeCondition)
{
	Vector2 backgroundPosition = { 0.0f,0.0f };
	float scale = 1.5f;

	BeginDrawing();
	if (player.score < changeCondition)
	{
		DrawTextureEx(gameplay_Background, backgroundPosition, 0, scale, WHITE);
	}
	else
	{
		DrawTextureEx(gameplay_Background2, backgroundPosition, 0, scale, WHITE);
	}

	ClearBackground(BLACK);
	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			drawBullet(player.playerAmmo[i]);
		}
	}

	drawPlayer(player);



	if (monster.isAlive)
	{
		drawMonster(monster);
	}

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



		float scale1 = 1.0f;

		Rectangle sourRect = { 0,0,static_cast<float>(pauseMenuTexture.width),static_cast<float>(pauseMenuTexture.height) };
		Rectangle destRect = { static_cast<float>(GetScreenWidth() / 2),static_cast<float>(GetScreenHeight() / 2),static_cast<float>(pauseMenuTexture.width * scale1),static_cast<float>(pauseMenuTexture.height * scale1) };
		Vector2 texturePiv = { static_cast<float>((pauseMenuTexture.width * scale1) / 2),static_cast<float>((pauseMenuTexture.height * scale1) / 2) };

		DrawTexturePro(pauseMenuTexture, sourRect, destRect, texturePiv, 0.0f, WHITE);

#if Debug
		drawButton(returnButton);
		drawButton(resetButton);
#endif // Debug
		if (player.lives <= 0)
		{
			int loseText = MeasureText("Perdiste", pauseButton.fontSize);
			DrawRectangle(static_cast<int>(pauseButton.rect.x - pauseButton.rect.width / 2), static_cast<int>(pauseButton.rect.y), static_cast<int>(pauseButton.rect.width * 2), static_cast<int>(pauseButton.rect.height * 3), WHITE);
			DrawText("Perdiste", static_cast<int>(GetScreenWidth() / 2 - loseText / 2), static_cast<int>(pauseButton.rect.y * 2.5f), pauseButton.fontSize, BLACK);
		}
		DrawText(TextFormat("High Score: %i", highScore), 6, 40, 30, PURPLE);

		drawButtonTexture(continueButton, continueTexture, continueTexture);
		drawButtonTexture(resetButton, resetTexture, resetTexture);
		drawButtonTexture(returnButton, returnTexture, returnTexture);
	}

	if (!pauseGameplay)
	{
		drawButtonTexture(pauseButton, pauseButtonTexture, pauseButtonTexture);
	}
	DrawText(TextFormat("Player Score: %i", player.score), 6, 6, 30, RED);

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

	DrawTextureEx(mouseTextureGameplay, GetMousePosition(), 0, 2.0f, WHITE);

	EndDrawing();
}
void updateGameplay()
{
	if (player.score > highScore)
	{
		highScore = player.score;
	}

	if (change)
	{
		if (!monster.isAlive)
		{
			if (monster.respawnTimer <= 0)
			{
				monster.isAlive = true;
				monster.lives = 3;
				monster.respawnTimer = 0;

			}
			else
			{
				monster.respawnTimer -= GetFrameTime();
				std::cout << "Respawn Timer : " << monster.respawnTimer << endl;
			}
		}
	}

	moveSpaceShip(player);

	if (monster.isAlive)
	{
		moveMonster(monster, { player.rect.x,player.rect.y });
	}

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

	if (monster.isAlive)
	{
		if (monster.isHit)
		{
			monster.hitTimer -= GetFrameTime();

			if (monster.hitTimer <= 0)
			{
				monster.isHit = false;
			}
			cout << "Hit Timer Monster : " << monster.hitTimer << endl;
		}
	}

	checkOutOfBounds();
	checkColitions();
	resetAsteroids();

	if (player.lives <= 0)
	{
		playerDead();
		pauseGameplay = true;
	}

	//std::cout << "Timer : " << timer << endl;

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
	checkMonsterOutOfBounds(screenWidth, screenHeight);
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
void checkMonsterOutOfBounds(int screenWidth, int screenHeight)
{
	if (monster.rect.x < 0)
	{
		monster.rect.x = static_cast<float>(screenWidth);
	}
	if (monster.rect.x > static_cast<float>(screenWidth))
	{
		monster.rect.x = 0;
	}
	if (monster.rect.y < 0)
	{
		monster.rect.y = static_cast<float>(screenHeight);
	}
	if (monster.rect.y > static_cast<float>(screenHeight))
	{
		monster.rect.y = 0;
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

	for (int i = 0; i < playerMaxAmmo; i++)
	{
		if (player.playerAmmo[i].isActive)
		{
			if (monster.isAlive)
			{
				bulletMonsterColition(player.playerAmmo[i]);
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

	if (monster.isAlive)
	{
		spaceshipMonsterColition();
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
		PlaySound(asteroidShotSound);

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
void bulletMonsterColition(Bullet& currentBullet)
{
	float distanceX = 0;
	float distanceY = 0;
	float distance = 0;

	distanceX = monster.rect.x - currentBullet.position.x;
	distanceY = monster.rect.y - currentBullet.position.y;

	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance < monster.rad + currentBullet.rad)
	{
		if (!monster.isHit)
		{
			currentBullet.isActive = false;
			reciveDamage(monster);
			if (monster.lives <= 0)
			{
				player.score += 50;
			}
			monster.isHit = true;
		}
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
void spaceshipMonsterColition()
{
	float distanceX = 0;
	float distanceY = 0;
	float distance = 0;

	distanceX = monster.rect.x - player.rect.x;
	distanceY = monster.rect.y - player.rect.y;

	distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance < player.rad + monster.rad)
	{
		if (!player.isHit && !monster.isHit)
		{
			player.acceleration.x = player.acceleration.x * -1.0f;
			player.acceleration.y = player.acceleration.y * -1.0f;

			monster.trayectory.x = monster.trayectory.x * -1.0f;
			monster.trayectory.y = monster.trayectory.y * -1.0f;

			player.lives--;
			reciveDamage(monster);

			if (monster.lives <= 0)
			{
				player.score += 50;
			}

			player.isHit = true;
			monster.isHit = true;
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
void mouseButtonColition(bool& initGame, bool& backToMenu)
{
	Vector2 mousePosition = { static_cast<float>(GetMouseX()),static_cast<float>(GetMouseY()) };

	if (CheckCollisionPointRec(mousePosition, pauseButton.rect))
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			pauseGameplay = true;
		}

	}
	if (pauseGameplay)
	{
		if (CheckCollisionPointRec(mousePosition, continueButton.rect))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				pauseGameplay = false;
			}
		}
		if (CheckCollisionPointRec(mousePosition, resetButton.rect))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				initGame = true;
			}
		}
		if (CheckCollisionPointRec(mousePosition, returnButton.rect))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				backToMenu = true;
			}
		}
	}
}