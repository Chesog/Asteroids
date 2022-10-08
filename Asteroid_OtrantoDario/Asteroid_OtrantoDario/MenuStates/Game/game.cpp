#include "game.h"

Texture2D spaceShipTexture;
Texture2D bulletTexture;

Texture2D largeAsteroidTexture;
Texture2D largeAsteroidTextureEvil;

Texture2D mediumAsteroidTexture;
Texture2D mediumAsteroidTextureEvil;

Texture2D smallAsteroidTexture;
Texture2D smallAsteroidTextureEvil;

Texture2D menu_Background;
Texture2D gameplay_Background;
Texture2D gameplay_Background2;

Texture2D Controls1;
Texture2D Controls2;

void ejecuteGame() 
{

    int screenWidth = 1280;
    int screenHeight = 720;

    int menuAnsw = (int)MenuStates::MainMenu;
    int point = 1;
    bool backToMenu = false;
    //bool exitGame = false;
    bool reset = true;


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
            initGame = true;
            menuAnsw = mainMenu(point);
            break;
        case (int)MenuStates::Gameplay:
            menuAnsw = gameplayLoop(initGame,backToMenu);
            break;
        case (int)MenuStates::Rules:
            menuAnsw = rulesLoop(backToMenu);
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
    unloadTextures();
    CloseWindow();
}

void loadTextures() 
{
    spaceShipTexture = LoadTexture("res/nave_pixelada.png");
    bulletTexture = LoadTexture("res/disparo-2.png");
    largeAsteroidTexture = LoadTexture("res/asteroide_lindo.png");
    mediumAsteroidTexture = LoadTexture("res/asteroide_lindo_mitad.png");
    smallAsteroidTexture = LoadTexture("res/asteroide_lindo_un_cuarto.png");


    largeAsteroidTextureEvil = LoadTexture("res/asteroide_malo.png");
    mediumAsteroidTextureEvil = LoadTexture("evilAsteroids-1.png");
    smallAsteroidTextureEvil = LoadTexture("res/evilAsroids-2.png");


    menu_Background = LoadTexture("res/fondo_turbio.png");
    gameplay_Background = LoadTexture("res/fondo_1.png");
    gameplay_Background2 = LoadTexture("res/fondo_turbio.png");

    Controls1 = LoadTexture("res/click_izquierdo.png");
    Controls2 = LoadTexture("res/click_derecho.png");
}
void unloadTextures() 
{
    UnloadTexture(spaceShipTexture);
    UnloadTexture(bulletTexture);
    UnloadTexture(largeAsteroidTexture);
    UnloadTexture(mediumAsteroidTexture);
    UnloadTexture(smallAsteroidTexture);
    UnloadTexture(menu_Background);
    UnloadTexture(gameplay_Background);
    UnloadTexture(gameplay_Background2);
    UnloadTexture(largeAsteroidTextureEvil);
    UnloadTexture(mediumAsteroidTextureEvil);
    UnloadTexture(smallAsteroidTextureEvil);
    UnloadTexture(Controls1);
    UnloadTexture(Controls2);
}