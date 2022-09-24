#include "bullet.h"

void drawBullet(Bullet bullet) 
{
	DrawCircle(bullet.position.x, bullet.position.y, bullet.rad, bullet.color);
}
void moveBullet(Bullet& bullet)
{
	bullet.position.x = bullet.position.x +  bullet.trayectory.x * bullet.speed.x * GetFrameTime();
	bullet.position.y = bullet.position.y +  bullet.trayectory.y * bullet.speed.y * GetFrameTime();
}