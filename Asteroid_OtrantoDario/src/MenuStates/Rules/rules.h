#pragma once
#include "raylib.h"
#include "MenuStates/GlobalEnums/genera_func.h"
#include "Objects/Button/button.h"

namespace cheso_Asteroids
{
	int rulesLoop(bool& backToMenu);
	void drawRules();
	void checkInputR(bool& backToMenu);
}