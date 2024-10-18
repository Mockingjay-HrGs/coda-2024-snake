#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#define TAILLE_BLOC 16
#define LARGEUR 320
#define HAUTEUR 320
#define MAX_SEGMENTS 100

#define LONGUEUR_VICTOIRE 10  

typedef struct {
    int x;
    int y;
} Segment;

void afficher_bloc(SDL_Renderer* renderer, int x, int y, SDL_Color color);

int collision_serpent(Segment serpent[], int longueur);

void generer_nourriture(int *nourriture_x, int *nourriture_y, Segment serpent[], int longueur_serpent);

void generer_pokeball(int *pokeball_x, int *pokeball_y, Segment serpent[], int longueur_serpent);

#endif
