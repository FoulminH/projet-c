#include "../includes/window.h"



Window *create_window(){
    Window *window = malloc(sizeof(Window));

    if(SDL_CreateWindowAndRenderer(WINDOW_WITDH, WINDOW_HEIGHT, 0, &window->sdl_window, &window->renderer) != 0){
        SDL_DestroyAndExit(window->renderer, window->sdl_window, "Impossible de créer la fenêtre et le renderer");
    }
    SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_SetRenderDrawBlendMode(window->renderer, SDL_BLENDMODE_BLEND);
    SDL_SetWindowTitle(window->sdl_window, "Pendu");
    SDL_RenderClear(window->renderer);
    SDL_RenderPresent(window->renderer);
    
    return window;
}

void destroy_window(Window *window)
{
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->sdl_window);
    free(window);
}


void displayImg(SDL_Window *window, SDL_Renderer *renderer, char* imgPath, int rect_x, int rect_y){
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;
    
    image = IMG_Load(imgPath);
    if(image == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger l'image");
    }                        
    texture = SDL_CreateTextureFromSurface(renderer,image);
    SDL_FreeSurface(image);
    if(texture == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer la texture");
    }

    SDL_Rect rectangle;
    if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger la texture");
    }
    rectangle.x = rect_x;
    rectangle.y = rect_y;

    if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible d'afficher la texture");
    }
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);
}

void displayTxt(SDL_Window *window, SDL_Renderer *renderer, char* fontPath, int fontSize, char* txt, int rect_x, int rect_y){
    SDL_Texture *texte_texture;
    TTF_Font *font = TTF_OpenFont(fontPath,fontSize);

    if(font == NULL){
        TTF_DestroyAndExit(renderer, window, "Impossible de charger la font");
    }
    SDL_Color noir = {0, 0, 0};
    SDL_Surface* texte = TTF_RenderText_Blended(font, txt, noir);

    texte_texture = SDL_CreateTextureFromSurface(renderer, texte);
    SDL_FreeSurface(texte);
    if(texte_texture == NULL){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de créer la texture");
    }

    SDL_Rect rectangle;
    if(SDL_QueryTexture(texte_texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible de charger la texture");
    }

    rectangle.x = rect_x;
    rectangle.y = rect_y;

    if(SDL_RenderCopy(renderer, texte_texture, NULL, &rectangle) != 0){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError("Impossible d'afficher la texture");
    }
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texte_texture);

}

void SDL_ExitWithError(char* message){
    SDL_Log("ERREUR : %s -> %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void TTF_ExitWithError(char* message){
    SDL_Log("ERREUR : %s -> %s\n", message, TTF_GetError());
    TTF_Quit();
    exit(EXIT_FAILURE);
}

void SDL_DestroyAndExit(SDL_Renderer *renderer, SDL_Window *window , char* message){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_ExitWithError(message);
}
void TTF_DestroyAndExit(SDL_Renderer *renderer, SDL_Window *window , char* message){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_ExitWithError(message);
}


void menu(SDL_Window *window, SDL_Renderer *renderer, char keyPressed, SDL_bool *program_launched, int *played, int *won, int *lose){
    char* char_played = malloc(sizeof(char));
    char* char_won = malloc(sizeof(char));
    char* char_lose = malloc(sizeof(char));
    SDL_itoa(*played, char_played, 10);
    SDL_itoa(*won, char_won, 10);
    SDL_itoa(*lose, char_lose, 10);
    SDL_RenderClear(renderer);
    displayImg(window, renderer, "img/main-menu-2.png", 0, 0);
    displayTxt(window, renderer, "font/absender1.ttf", 30, "Statistiques :", 10, 100);
    displayTxt(window, renderer, "font/absender1.ttf", 30, "Parties jouees :", 50, 200);
    displayTxt(window, renderer, "font/absender1.ttf", 30, char_played, 300, 200);
    displayTxt(window, renderer, "font/absender1.ttf", 30, "Parties gagnees :", 400, 200);
    displayTxt(window, renderer, "font/absender1.ttf", 30, char_won, 650, 200);
    displayTxt(window, renderer, "font/absender1.ttf", 30, "Parties perdues :", 800, 200);
    displayTxt(window, renderer, "font/absender1.ttf", 30, char_lose, 1050, 200);
}
