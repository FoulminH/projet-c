#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "window.h"

char Norme(char keyPressed);
int CompareChar(char c1,char c2);
int CompareChaine(char chaine1[],char chaine2[]);
void GenMot(FILE *fichier,char chaine[]);
void InitialChaine(char chaine[],char c,int nb);
int LettreUtilise(char c,char chaine[]);
void PlacerCar(char,char[]);
void game(SDL_Window *window, SDL_Renderer *renderer, char keyPressed, SDL_bool *program_launched);
char proposition(SDL_bool *program_launched);
void displayPendu(SDL_Window *window, SDL_Renderer *renderer, int nbErreur);