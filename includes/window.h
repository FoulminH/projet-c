#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define WINDOW_WITDH 1152
#define WINDOW_HEIGHT 720

#define WORD_X 500
#define WORD_Y 300
#define WORD_SIZE 150
#define TENTATIVE_SIZE 50
#define TXT_TENTATIVE_X 50
#define TXT_TENTATIVE_Y 50
#define INT_TENTATIVE_X 350
#define INT_TENTATIVE_Y 50
#define ACTUAL_WORD_X 400
#define ACTUAL_WORD_Y 200
#define PSEUDO_X 450
#define PSEUDO_Y 340


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
void menu(SDL_Window *window, SDL_Renderer *renderer, char keyPressed, SDL_bool *program_launched,int *played, int *won, int *lost);
