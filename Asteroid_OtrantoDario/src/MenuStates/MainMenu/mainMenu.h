#pragma once
#include "raylib.h"
#include "MenuStates/GlobalEnums/genera_func.h"
#include "Objects/Button/button.h"


	void drawMenu(int screenWidth, int screenHeight);
	int checkInput(int& point);
	int mainMenu(int& point);
	int checkMouseColition(Vector2 mousePosition, int& point);

