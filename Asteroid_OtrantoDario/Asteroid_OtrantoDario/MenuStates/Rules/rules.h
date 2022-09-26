#pragma once
#include "raylib.h"
#include "../Asteroid_OtrantoDario/MenuStates/GlobalEnums/genera_func.h"


int rulesLoop(bool& backToMenu, Color colorPlayer1, Color colorPlayer2);
void drawRules(Color colorPlayer1, Color colorPlayer2);
void checkInputR(bool& backToMenu);