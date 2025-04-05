#include "fonction.h"

SDL_Window *creerFenetre(char nom[])
{
    SDL_Window *nv = SDL_CreateWindow(nom, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      LONGUEUR_FENETRE, LARGEUR_FENETRE, SDL_WINDOW_SHOWN);
    if (nv == NULL)
    {
        printf("Erreur d'allocation !\n");
        SDL_Quit();
        exit(1);
    }
    return nv;
}

SDL_Renderer *creerRenderer(SDL_Window *fenetre)
{
    SDL_Renderer *renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Erreur d'allocation du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        exit(1);
    }
    return renderer;
}

void dessinerCarre(SDL_Renderer *renderer, SDL_Rect carre)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &carre);

    SDL_RenderPresent(renderer);
}

void gererEvenements(SDL_bool *continuer, SDL_Rect *carre, SDL_bool *enSaut, float *vitesseSaut, Touches *touches)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            *continuer = SDL_FALSE;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                touches->gauche = SDL_TRUE;
                break;

            case SDLK_d:
                touches->droite = SDL_TRUE;
                break;

            case SDLK_SPACE:
                touches->saut = SDL_TRUE;
                break;

            case SDLK_ESCAPE:
                *continuer = SDL_FALSE;
                break;
            }
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_q:
                touches->gauche = SDL_FALSE;
                break;

            case SDLK_d:
                touches->droite = SDL_FALSE;
                break;
            }
            break;
        }
    }
}

int map[MAP_HAUTEUR][MAP_LARGEUR];

void initialiserMap()
{
    // Vider la map
    for (int i = 0; i < MAP_HAUTEUR; i++)
        for (int j = 0; j < MAP_LARGEUR; j++)
            map[i][j] = 0;

    // Sol
    for (int x = 0; x < MAP_LARGEUR; x++)
        map[MAP_HAUTEUR - 2][x] = 1;

    // Plateformes
    for (int x = 5; x < 10; x++)
        map[MAP_HAUTEUR - 3][x] = 2;
    for (int x = 15; x < 20; x++)
        map[MAP_HAUTEUR - 5][x] = 2;
    for (int x = 25; x < 30; x++)
        map[MAP_HAUTEUR - 7][x] = 2;
    for (int x = 35; x < 40; x++)
        map[MAP_HAUTEUR - 9][x] = 2;
    for (int x = 45; x < 50; x++)
        map[MAP_HAUTEUR - 11][x] = 2;
    // Ajoute d'autres platforme originales, tu ne peut pas dépase la hauteur de 12
    for (int x = 55; x < 60; x++)
        map[MAP_HAUTEUR - 3][x] = 2;
    for (int x = 65; x < 70; x++)
        map[MAP_HAUTEUR - 5][x] = 2;
    for (int x = 75; x < 80; x++)
        map[MAP_HAUTEUR - 7][x] = 2;
    for (int x = 85; x < 90; x++)
        map[MAP_HAUTEUR - 9][x] = 2;
    for (int x = 95; x < 100; x++)
        map[MAP_HAUTEUR - 11][x] = 2;
    // Ajoute d'autres platforme originales, tu ne peut pas dépase la hauteur de 12
    for (int x = 105; x < 110; x++)
        map[MAP_HAUTEUR - 3][x] = 2;
    for (int x = 115; x < 120; x++)
        map[MAP_HAUTEUR - 5][x] = 2;
    map[5][198] = 2;
}

void dessinerMap(SDL_Renderer *renderer, int cameraX)
{
    for (int y = 0; y < MAP_HAUTEUR; y++)
    {
        for (int x = 0; x < MAP_LARGEUR; x++)
        {
            SDL_Rect bloc = {
                x * BLOC_SIZE - cameraX,
                y * BLOC_SIZE,
                BLOC_SIZE,
                BLOC_SIZE};

            switch (map[y][x])
            {
            case 1:                                                 // Sol
                SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255); // marron
                SDL_RenderFillRect(renderer, &bloc);
                break;
            case 2:                                                   // Plateforme
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // gris
                SDL_RenderFillRect(renderer, &bloc);
                break;
            default:
                // Rien à dessiner
                break;
            }
        }
    }
}