#pragma once
#pragma once
#include "raylib.h"
#include "MenuStates/GlobalEnums/genera_func.h"
#include "Objects/Button/button.h"

namespace cheso_Asteroids
{
	int creditsLoop(bool& backToMenu);
	void drawCredits();
	void checkInput(bool& backToMenu);
}
