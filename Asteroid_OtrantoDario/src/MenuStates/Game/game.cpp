#include "game.h"

extern Texture2D spaceShipTexture;
extern Texture2D bulletTexture;
extern Texture2D monsterTexture;

extern Texture2D largeAsteroidTexture;
extern Texture2D largeAsteroidTextureEvil;

extern Texture2D mediumAsteroidTexture;
extern Texture2D mediumAsteroidTextureEvil;

extern Texture2D smallAsteroidTexture;
extern Texture2D smallAsteroidTextureEvil;

extern Texture2D menu_Background;
extern Texture2D menu_Background1;
extern Texture2D gameplay_Background;
extern Texture2D gameplay_Background2;
extern Texture2D CreditsBackground;
extern Texture2D CreditsBackground2;
extern Texture2D optionsBackground;
extern Texture2D rulesBackground;

extern Texture2D playTexture;
extern Texture2D rulesTexture;
extern Texture2D optionsTexture;
extern Texture2D creditsTexture;
extern Texture2D exitTexture;

extern Texture2D continueTexture;
extern Texture2D resetTexture;
extern Texture2D returnTexture;
extern Texture2D pauseButtonTexture;

extern Texture2D menuLogo;

extern Texture2D Controls1;
extern Texture2D Controls2;

extern Texture2D pauseMenuTexture;

extern Music menuMusic;
extern Music gameplayMusic;

extern Sound shotSound;
extern Sound asteroidShotSound;
extern Sound deadSpaceshipSound;

extern int highScore;

float timer = 0;

void loadTextures();
void loadSounds();
void unloadTextures();
void unloadSounds();

void ejecuteGame() 
{

    //int screenWidth = 1280;
    //int screenHeight = 720;

    int screenWidth = 1024;
    int screenHeight = 768;

    int menuAnsw = (int)MenuStates::MainMenu;
    int point = 1;
    bool backToMenu = false;
    bool reset = true;



    InitWindow(screenWidth, screenHeight, "Asteroids");

    //ToggleFullscreen();
    InitAudioDevice();
    highScore = LoadStorageValue(0);
    loadTextures();
    loadSounds();

    SetExitKey(KEY_NULL);

    SetMusicVolume(menuMusic,0.5f);
    SetMusicVolume(gameplayMusic,0.1f);
    SetSoundVolume(asteroidShotSound,0.3f);

    bool initGame = true;


    while (!WindowShouldClose())
    {
        switch (menuAnsw)
        {
        case (int)MenuStates::MainMenu:
            backToMenu = false;
            reset = true;
            initGame = true;
            StopMusicStream(gameplayMusic);
            PlayMusicStream(menuMusic);
            menuAnsw = mainMenu(point);
            break;
        case (int)MenuStates::Gameplay:
            StopMusicStream(menuMusic);
            PlayMusicStream(gameplayMusic);
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
    unloadSounds();
    CloseAudioDevice();

    CloseWindow();
}
void loadTextures() 
{
    spaceShipTexture = LoadTexture("res/nave_pixelada.png");
    bulletTexture = LoadTexture("res/disparo-2.png");
    monsterTexture = LoadTexture("res/monster.png");

    largeAsteroidTexture = LoadTexture("res/asteroide_lindo.png");
    mediumAsteroidTexture = LoadTexture("res/asteroide_lindo_mitad.png");
    smallAsteroidTexture = LoadTexture("res/asteroide_lindo_un_cuarto.png");


    largeAsteroidTextureEvil = LoadTexture("res/asteroide_malo.png");
    mediumAsteroidTextureEvil = LoadTexture("res/asteroide_malo.png");
    smallAsteroidTextureEvil = LoadTexture("res/evilAsroids-2.png");

    playTexture = LoadTexture("res/jugar.png");
    rulesTexture = LoadTexture("res/reglas.png");
    optionsTexture = LoadTexture("res/opciones.png");
    creditsTexture = LoadTexture("res/credits.png");
    exitTexture = LoadTexture("res/salir.png");

    continueTexture = LoadTexture("res/continuar.png");
    resetTexture = LoadTexture("res/reiniciar.png");
    returnTexture = LoadTexture("res/volver_al_menu.png");
    pauseButtonTexture = LoadTexture("res/boton_blanco_pausa.png");

    menu_Background = LoadTexture("res/menu_light_sin_letras.png");
    menu_Background1 = LoadTexture("res/fondo_1.png");
    gameplay_Background = LoadTexture("res/fondo_1.png");
    gameplay_Background2 = LoadTexture("res/fondo_turbio.png");
    CreditsBackground =  LoadTexture("res/pagina_creditos_1.png");
    CreditsBackground2 = LoadTexture("res/pagina_creditos_2.png");
    optionsBackground = LoadTexture("res/fondo_turbio.png");
    rulesBackground = LoadTexture("res/fondo_turbio.png");

    menuLogo = LoadTexture("res/logoDeepPurple.png");

    Controls1 = LoadTexture("res/click_izquierdo.png");
    Controls2 = LoadTexture("res/click_derecho.png");

    pauseMenuTexture = LoadTexture("res/menu_pausa_sin_letras.png");
}
void loadSounds() 
{
    menuMusic = LoadMusicStream("res/Music/menu_song.wav");
    gameplayMusic = LoadMusicStream("res/Music/juego_song.wav");

    shotSound = LoadSound("res/Music/shot.wav");
    asteroidShotSound = LoadSound("res/Music/dead_asteroid.wav");
    deadSpaceshipSound = LoadSound("res/Music/dead_explotion.wav");
}
void unloadTextures() 
{
    UnloadTexture(spaceShipTexture);
    UnloadTexture(bulletTexture);
    UnloadTexture(monsterTexture);

    UnloadTexture(largeAsteroidTexture);
    UnloadTexture(mediumAsteroidTexture);
    UnloadTexture(smallAsteroidTexture);
    UnloadTexture(largeAsteroidTextureEvil);
    UnloadTexture(mediumAsteroidTextureEvil);
    UnloadTexture(smallAsteroidTextureEvil);

    UnloadTexture(playTexture);
    UnloadTexture(rulesTexture);
    UnloadTexture(optionsTexture);
    UnloadTexture(creditsTexture);
    UnloadTexture(exitTexture);

    UnloadTexture(continueTexture);
    UnloadTexture(resetTexture);
    UnloadTexture(returnTexture);
    UnloadTexture(pauseButtonTexture);

    UnloadTexture(menu_Background);
    UnloadTexture(menu_Background1);
    UnloadTexture(gameplay_Background);
    UnloadTexture(gameplay_Background2);
    UnloadTexture(CreditsBackground);
    UnloadTexture(CreditsBackground2);
    UnloadTexture(optionsBackground);
    UnloadTexture(rulesBackground);

    UnloadTexture(menuLogo);
    UnloadTexture(Controls1);
    UnloadTexture(Controls2);

    UnloadTexture(pauseMenuTexture);
}
void unloadSounds() 
{
    UnloadMusicStream(menuMusic);
    UnloadMusicStream(gameplayMusic);

    UnloadSound(shotSound);
    UnloadSound(asteroidShotSound);
    UnloadSound(deadSpaceshipSound);
}