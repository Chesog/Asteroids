#include "game.h"

Texture2D spaceShipTexture;
Texture2D bulletTexture;
Texture2D largeAsteroidTexture;
Texture2D mediumAsteroidTexture;
Texture2D smallAsteroidTexture;

Texture2D menu_Background;
Texture2D gameplay_Background;

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
            initGame = true;
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
    spaceShipTexture = LoadTexture("res/nave_pixelada.png");
    bulletTexture = LoadTexture("res/disparo-2.png");
    largeAsteroidTexture = LoadTexture("res/asteroide_lindo.png");
    mediumAsteroidTexture = LoadTexture("res/asteroide_lindo_mitad_2.png");
    smallAsteroidTexture = LoadTexture("res/asteroide_lindo_mitad.png");
    menu_Background = LoadTexture("res/fondo_turbio.png");
    gameplay_Background = LoadTexture("res/fondo_1.png");
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
}