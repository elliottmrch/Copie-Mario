#include "fonction.h"

int main(int argc, char *argv[])
{
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        printf("Erreur SDL_Init : %s", SDL_GetError());
        return 1;
    }

    SDL_Window *fenetreJeu = creerFenetre("Mario");
    SDL_Renderer *renderer = creerRenderer(fenetreJeu);

    SDL_Rect carre = {100, SOL, 50, 50};

    SDL_bool enSaut = SDL_FALSE;
    float vitesseSaut = 0;
    Touches touches = {SDL_FALSE, SDL_FALSE, SDL_FALSE};

    int cameraX = 0;
    initialiserMap();

    SDL_bool continuer = SDL_TRUE;
    while (continuer)
    {
        gererEvenements(&continuer, &carre, &enSaut, &vitesseSaut, &touches);

        if (touches.gauche)
        {
            carre.x -= VITESSE_DEPLACEMENT;
            if (carre.x < 0)
                carre.x = 0;
        }
        if (touches.droite)
        {
            carre.x += VITESSE_DEPLACEMENT;
            // if (carre.x > LONGUEUR_FENETRE - carre.w)
            //     carre.x = LONGUEUR_FENETRE - carre.w;
            if (carre.x > MAP_LARGEUR * BLOC_SIZE - carre.w)
                carre.x = MAP_LARGEUR * BLOC_SIZE - carre.w;
        }

        if (enSaut)
        {
            carre.y += vitesseSaut;
            vitesseSaut += GRAVITE;

            if (carre.y >= SOL)
            {
                carre.y = SOL;
                enSaut = SDL_FALSE;
                vitesseSaut = 0;
            }
        }
        else if (touches.saut)
        {
            enSaut = SDL_TRUE;
            vitesseSaut = FORCE_SAUT;
            touches.saut = SDL_FALSE;
        }

        // Mise à jour de la caméra
        cameraX = carre.x + carre.w / 2 - LONGUEUR_FENETRE / 2;
        if (cameraX < 0)
            cameraX = 0;
        if (cameraX > MAP_LARGEUR * BLOC_SIZE - LONGUEUR_FENETRE)
            cameraX = MAP_LARGEUR * BLOC_SIZE - LONGUEUR_FENETRE;

        SDL_SetRenderDrawColor(renderer, 129, 212, 250, 255); // ciel
        SDL_RenderClear(renderer);

        // Décor
        dessinerMap(renderer, cameraX);

        // Perso
        dessinerCarre(renderer, (SDL_Rect){carre.x - cameraX, carre.y, carre.w, carre.h});

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetreJeu);
    SDL_Quit();
    return 0;
}