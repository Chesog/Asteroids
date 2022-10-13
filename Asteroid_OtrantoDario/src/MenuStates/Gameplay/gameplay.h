#pragma once
#include"raylib.h"
#include "raymath.h"
#include "Objects/Asteroids/asteroid.h"
#include "Objects/Spaceship/spaceship.h"
#include "MenuStates/GlobalEnums/genera_func.h"
#include "Objects/Button/button.h"
#include "Objects/Monster/monster.h"

namespace cheso_Asteroids
{
	int gameplayLoop(bool& initGame, bool& backToMenu);
}