#include "game.h"

static Texture2D spaceShip;
static Texture2D bullet;
static Texture2D LargeAsteroid;

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
            menuAnsw = gameplayLoop(initGame,spaceShip, bullet, LargeAsteroid);
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
    spaceShip = LoadTexture("res/nave 2.png");
    bullet = LoadTexture("res/disparo-2.png");
    LargeAsteroid = LoadTexture("res/metiorito lindo 2.png");
}
void unloadTextures() 
{
    UnloadTexture(spaceShip);
}