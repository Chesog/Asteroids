#pragma once
#include "raylib.h"
#include "MenuStates/GlobalEnums/genera_func.h"

struct Monster
{
	int lives;

	float rad;
	float rotation;
	float respawnTimer;
	float hitTimer;
	float attakTimer;
	float lockTimer;

	bool isAlive;
	bool isHit;

	Vector2 piv;
	Vector2 speed;
	Vector2 trayectory;

	Rectangle rect;
	Color monsterColor;
	Texture2D monsterTexture;
};
Monster initMonster(Texture2D monsterTexture);
void moveMonster(Monster& currentMonster, Vector2 target);
void reciveDamage(Monster& currentMonster);
void drawMonster(Monster& currentMonster);