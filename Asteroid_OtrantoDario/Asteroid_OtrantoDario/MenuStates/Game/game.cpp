#include "game.h"

void ejecuteGame() 
{
    //int screenHeight = 720;
//int screenWidth = 1280;

    int screenWidth = 1280;
    int screenHeight = 720;

    int menuAnsw = (int)MenuStates::MainMenu;
    int point = 1;
    bool backToMenu = false;
    bool exitGame = false;
    bool reset = true;
    Color colorPlayer1 = LIME;
    Color colorPlayer2 = BLUE;


    InitWindow(screenWidth, screenHeight, "Asteroids");
    //ToggleFullscreen();
    SetExitKey(KEY_NULL);

    SetTargetFPS(60);

    bool initGame = true;


    while (!WindowShouldClose())
    {
        switch (menuAnsw)
        {
        case (int)MenuStates::MainMenu:
            backToMenu = false;
            reset = true;
            menuAnsw = mainMenu(point);
            break;
        case (int)MenuStates::Gameplay:
            menuAnsw = gameplayLoop(initGame);
            break;
        case (int)MenuStates::Rules:
            menuAnsw = rulesLoop(backToMenu, colorPlayer1, colorPlayer2);
            break;
        case (int)MenuStates::Credits:
            menuAnsw = creditsLoop(backToMenu);
            break;
        case (int)MenuStates::Options:
            menuAnsw = optionsLoop(backToMenu, screenWidth, screenHeight);
            break;
        case (int)MenuStates::Exit:
            return;
            break;
        }
    }

    CloseWindow();
}