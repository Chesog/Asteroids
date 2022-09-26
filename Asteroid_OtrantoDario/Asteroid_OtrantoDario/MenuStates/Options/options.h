#pragma once
#include "raylib.h"
#include "../Asteroid_OtrantoDario/MenuStates/GlobalEnums/genera_func.h"
#include "../Asteroid_OtrantoDario/Objects/Button/button.h"


enum class OptionsResolution { DefaultResolution = 1, MaxResolution };


int optionsLoop(bool& backToMenu, int& screenWidth, int& screenHeight);
int checkInputOptions(bool& backToMenu, int& point);
void drawOptions(int point, Rectangle defaultResolution, Rectangle maxResolution);
void createOptionsButtons(Rectangle& defaultResolution, Rectangle& maxResolution);
