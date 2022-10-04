#include "game.h"

Texture2D spaceShipTexture;
Texture2D bulletTexture;
Texture2D largeAsteroidTexture;

void ejecuteGame() 
{
    //int screenHeight = 720;
//int screenWidth = 1280;

    int screenWidth = 1280;
    int screenHeight = 720;

    int menuAnsw = (int)MenuStates::MainMenu;
    int point = 1;
    bool backToMenu = false;
    //bool exitGame = false;
    bool reset = true;
    Color colorPlayer1 = LIME;
    Color colorPlayer2 = BLUE;


    InitWindow(screenWidth, screenHeight, "Asteroids");
    //ToggleFullscreen();

    loadTextures();

    SetExitKey(KEY_NULL);

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

void loadTextures() 
{
    spaceShipTexture = LoadTexture("res/nave 2.png");
    bulletTexture = LoadTexture("res/disparo-2.png");
    largeAsteroidTexture = LoadTexture("res/metiorito lindo 2.png");
}
void unloadTextures() 
{
    UnloadTexture(spaceShipTexture);
}