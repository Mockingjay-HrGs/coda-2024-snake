#include "snake_game.h"

void afficher_bloc(SDL_Renderer* renderer, int x, int y, SDL_Color color) {
    SDL_Rect bloc = {x, y, TAILLE_BLOC, TAILLE_BLOC};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &bloc);
}

int collision_serpent(Segment serpent[], int longueur) {
    for (int i = 1; i < longueur; i++) {
        if (serpent[0].x == serpent[i].x && serpent[0].y == serpent[i].y) {
            return 1;
        }
    }
    return 0; 
}

void generer_nourriture(int *nourriture_x, int *nourriture_y, Segment serpent[], int longueur_serpent) {
    int collision;
    do {
        collision = 0;
        *nourriture_x = (rand() % (LARGEUR / TAILLE_BLOC)) * TAILLE_BLOC;
        *nourriture_y = (rand() % (HAUTEUR / TAILLE_BLOC)) * TAILLE_BLOC;

        for (int i = 0; i < longueur_serpent; i++) {
            if (serpent[i].x == *nourriture_x && serpent[i].y == *nourriture_y) {
                collision = 1;
                break;
            }
        }
    } while (collision);
}

void generer_pokeball(int *pokeball_x, int *pokeball_y, Segment serpent[], int longueur_serpent) {
    int collision;
    do {
        collision = 0;
        *pokeball_x = (rand() % (LARGEUR / TAILLE_BLOC)) * TAILLE_BLOC;
        *pokeball_y = (rand() % (HAUTEUR / TAILLE_BLOC)) * TAILLE_BLOC;

        for (int i = 0; i < longueur_serpent; i++) {
            if (serpent[i].x == *pokeball_x && serpent[i].y == *pokeball_y) {
                collision = 1;
                break;
            }
        }
    } while (collision);
}
