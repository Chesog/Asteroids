#include "game.h"

void ejecuteGame() 
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Asteroids");

    SetTargetFPS(60);

    bool initGame = true;

    int menuAnsw = (int)MenuStates::Gameplay;

    while (!WindowShouldClose())
    {
        switch (menuAnsw)
        {
        case (int)MenuStates::MainMenu:
            break;
        case (int)MenuStates::Gameplay:
            menuAnsw = gameplayLoop(initGame);
            break;
        case (int)MenuStates::Rules:
            break;
        case (int)MenuStates::Options:
            break;
        case (int)MenuStates::Exit:
            break;
        }
    }

    CloseWindow();
}