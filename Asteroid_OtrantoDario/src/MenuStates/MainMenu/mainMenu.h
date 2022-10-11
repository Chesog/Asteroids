#pragma once
#include "raylib.h"
#include "MenuStates/GlobalEnums/genera_func.h"
#include "Objects/Button/button.h"


	void drawMenu(int screenWidth, int screenHeight, Button button1, Button button2, Button button3, Button button4, Button button5, int point);
	int checkInput(int& point);
	int mainMenu(int& point);
	int checkMouseColition(Vector2 mousePosition, Button button1, Button button2, Button button3, Button button4, Button button5, int& point);

