#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "window.h"

char* strToLower(char* str1, char* str2);
char* strToUpper(char* str1, char* str2);
char Norme(char keyPressed);
int CompareChar(char c1,char c2);
int CompareChaine(char chaine1[],char chaine2[]);
void GenMot(FILE *fichier,char chaine[]);
void InitialChaine(char chaine[],char c,int nb);
int LettreUtilise(char c,char chaine[]);
void quit_game(SDL_bool *inGame, SDL_bool *inMenu);
void game(SDL_Window *window, SDL_Renderer *renderer, char keyPressed, SDL_bool *inGame, SDL_bool *inMenu, int *played, int *won, int *lose);
char proposition(SDL_bool *inGame, SDL_bool *inMenu, int tentative);
void displayPendu(SDL_Window *window, SDL_Renderer *renderer, int tentative);
//liste chainée
typedef struct Node Node;
void add_to_end(Node *n, int value);
Node *search_value(Node *n, int value);
void display(Node *list);
void free_list(Node *n);

void addWordMenu(SDL_Window *window, SDL_Renderer *renderer,SDL_bool *addWord,SDL_bool *inMenu);
