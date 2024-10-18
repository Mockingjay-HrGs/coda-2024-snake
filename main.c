#include "snake_game.h"


#define LONGUEUR_VICTOIRE 10  

int main() {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        printf("Erreur d'initialisation de SDL2: %s\n", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("Erreur d'initialisation de SDL_Image: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR, HAUTEUR, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur de création du renderer: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* surface_nourriture = IMG_Load("kinder.png");
    if (surface_nourriture == NULL) {
        printf("Erreur de chargement de l'image Kinder: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture* texture_nourriture = SDL_CreateTextureFromSurface(renderer, surface_nourriture);
    SDL_FreeSurface(surface_nourriture);

    SDL_Surface* surface_pokeball = IMG_Load("pokepoke.png");
    if (surface_pokeball == NULL) {
        printf("Erreur de chargement de l'image Pokéball: %s\n", IMG_GetError());
        return 1;
    }
    SDL_Texture* texture_pokeball = SDL_CreateTextureFromSurface(renderer, surface_pokeball);
    SDL_FreeSurface(surface_pokeball);

    Segment serpent[MAX_SEGMENTS];
    int longueur_serpent = 1;
    serpent[0].x = LARGEUR / 2;
    serpent[0].y = HAUTEUR / 2;

    int nourriture_x, nourriture_y;
    generer_nourriture(&nourriture_x, &nourriture_y, serpent, longueur_serpent);

    int pokeball_x = -1, pokeball_y = -1;
    int pokeball_visible = 0;
    int compteur_pokeball = 0;

    SDL_Color couleur_serpent = {0, 255, 0, 255};  
    SDL_Color couleur_mur = {255, 0, 0, 255};      

    int direction_x = 0;
    int direction_y = 0;

    int running = 1;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                        direction_x = 0;
                        direction_y = -TAILLE_BLOC;
                        break;
                    case SDL_SCANCODE_S:
                        direction_x = 0;
                        direction_y = TAILLE_BLOC;
                        break;
                    case SDL_SCANCODE_A:
                        direction_x = -TAILLE_BLOC;
                        direction_y = 0;
                        break;
                    case SDL_SCANCODE_D:
                        direction_x = TAILLE_BLOC;
                        direction_y = 0;
                        break;
                    default:
                        break;
                }
            }
        }

        for (int i = longueur_serpent - 1; i > 0; i--) {
            serpent[i] = serpent[i - 1];
        }
        serpent[0].x += direction_x;
        serpent[0].y += direction_y;

        if (serpent[0].x < 0 || serpent[0].x >= LARGEUR || serpent[0].y < 0 || serpent[0].y >= HAUTEUR) {
            printf("Collision avec un mur !\n");
            running = 0; 
        }

        if (collision_serpent(serpent, longueur_serpent)) {
            printf("Collision avec soi-même !\n");
            running = 0; 
        }

        if (longueur_serpent >= LONGUEUR_VICTOIRE) {
            printf("Félicitations ! Vous avez gagné !\n");
            running = 0; 
        }

        if (serpent[0].x == nourriture_x && serpent[0].y == nourriture_y) {
            if (longueur_serpent < MAX_SEGMENTS) {
                longueur_serpent++;
            }
            generer_nourriture(&nourriture_x, &nourriture_y, serpent, longueur_serpent); 
        }

        compteur_pokeball++;
        if (compteur_pokeball >= 10 && !pokeball_visible) {
            generer_pokeball(&pokeball_x, &pokeball_y, serpent, longueur_serpent);
            pokeball_visible = 1;
            compteur_pokeball = 0;
        }

        if (pokeball_visible && serpent[0].x == pokeball_x && serpent[0].y == pokeball_y) {
            printf("Tu t'es fait attrapé(e) !\n");
            running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < LARGEUR; i += TAILLE_BLOC) {
            afficher_bloc(renderer, i, 0, couleur_mur);
            afficher_bloc(renderer, i, HAUTEUR - TAILLE_BLOC, couleur_mur);
        }
        for (int i = 0; i < HAUTEUR; i += TAILLE_BLOC) {
            afficher_bloc(renderer, 0, i, couleur_mur);
            afficher_bloc(renderer, LARGEUR - TAILLE_BLOC, i, couleur_mur);
        }

        for (int i = 0; i < longueur_serpent; i++) {
            afficher_bloc(renderer, serpent[i].x, serpent[i].y, couleur_serpent);
        }

        SDL_Rect rect_nourriture = {nourriture_x, nourriture_y, TAILLE_BLOC, TAILLE_BLOC};
        SDL_RenderCopy(renderer, texture_nourriture, NULL, &rect_nourriture);

        if (pokeball_visible) {
            SDL_Rect rect_pokeball = {pokeball_x, pokeball_y, TAILLE_BLOC, TAILLE_BLOC};
            SDL_RenderCopy(renderer, texture_pokeball, NULL, &rect_pokeball);
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyTexture(texture_nourriture);
    SDL_DestroyTexture(texture_pokeball);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
