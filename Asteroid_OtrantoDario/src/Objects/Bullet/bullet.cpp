#include "bullet.h"

namespace cheso_Asteroids
{
	void initBullet(Bullet& currentBullet, Texture2D bulletTexture)
	{

		currentBullet.position = { 0,0 };
		currentBullet.trayectory = { 0,0 };
		currentBullet.speed = { 500.0f,500.0f };
		currentBullet.rad = 4.0f;
		currentBullet.isActive = false;
		currentBullet.bulletTexture = bulletTexture;
		currentBullet.color = RED;

	}
	void drawBullet(Bullet bullet)
	{
#if _DEBUG
		DrawCircle(static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), bullet.rad, bullet.color);
#endif // _DEBUG

		Rectangle sourRect = { 0.0f,0.0f,static_cast<float>(bullet.bulletTexture.width),static_cast<float>(bullet.bulletTexture.height) };
		Rectangle destRect = { bullet.position.x,bullet.position.y,sourRect.width,sourRect.height };
		Vector2 texturePiv = { static_cast<float>(bullet.bulletTexture.width / 2),static_cast<float>(bullet.bulletTexture.height / 2) };

		DrawTexturePro(bullet.bulletTexture, sourRect, destRect, texturePiv, bullet.rotation + 90, WHITE);
	}
	void moveBullet(Bullet& bullet)
	{
		bullet.position.x = bullet.position.x + bullet.trayectory.x * bullet.speed.x * GetFrameTime();
		bullet.position.y = bullet.position.y + bullet.trayectory.y * bullet.speed.y * GetFrameTime();
	}
}