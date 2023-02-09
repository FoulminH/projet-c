#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define WINDOW_WITDH 1152
#define WINDOW_HEIGHT 720

#define WORD_X 500
#define WORD_Y 300
#define WORD_SIZE 150

typedef struct {
    SDL_Window *sdl_window;
    SDL_Renderer *renderer;
} Window;

Window *create_window();

void destroy_window(Window *window);
void displayImg(SDL_Window *window, SDL_Renderer *renderer, char* imgPath, int rect_x, int rect_y);
void displayTxt(SDL_Window *window, SDL_Renderer *renderer, char* fontPath, int fontSize, char* txt, int rect_x, int rect_y);
void SDL_ExitWithError(char* message);
void TTF_ExitWithError(char* message);
void SDL_DestroyAndExit(SDL_Renderer *renderer, SDL_Window *window , char* message);
void TTF_DestroyAndExit(SDL_Renderer *renderer, SDL_Window *window , char* message);

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
//void getMousePosition(int *mouse_x, int *mouse_y);

