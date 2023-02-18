/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>*/
#include <stdio.h>
#include <stdlib.h>
//#include "includes/functions.h"
//#include "includes/window.h"
#include "includes/game.h"

int main(int argc, char *argv[])
{
    //Initialisation des variables (graphiques)
    Window *window = create_window();
    //Initialisation des variables (jeu)
    SDL_bool program_launched = SDL_TRUE;
    char keyPressed = '\b';
    int mouse_x, mouse_y;
    SDL_bool isMouseOnQuit = SDL_FALSE;
    SDL_bool isMouseOnPlay = SDL_FALSE;
    SDL_bool isMouseOnAdd = SDL_FALSE;
    SDL_bool inGame = SDL_FALSE;
    SDL_bool inMenu = SDL_FALSE;
    SDL_bool addWord = SDL_FALSE;
    SDL_bool askPseudo = SDL_FALSE;
    SDL_Event event;
    int* score = malloc(sizeof(int));
    *score = 0;
    ///////////////////////////////////////////// A REMPLACER PAR LES REQUETES SQL /////////////////////////////////////////////
    int *played = malloc(sizeof(int));
    *played = 0;
    int *won = malloc(sizeof(int));
    *won = 0;
    int *lose = malloc(sizeof(int));
    *lose = 0;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) // Initialisation de la SDL & gestion des erreurs
    {
        SDL_ExitWithError("Initialisation SDL :(");
    }

    if(TTF_Init() != 0){
        TTF_ExitWithError("Initialisation TTF :(");
    }
    // pour taper du texte directement
    SDL_StartTextInput();
    char* textInput = malloc(sizeof(char)*30);
    textInput[0] = '\0';
    char* pseudo = malloc(sizeof(char)*30);

    //début du programme
    displayImg(window->sdl_window,window->renderer, "img/askPseudo.png",0,0);
    askPseudo = SDL_TRUE;                         
    while(program_launched){
        SDL_WaitEvent(&event);
            switch(event.type){
                //obtenir la position de la souris
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouse_x,&mouse_y);
                    //position de la souris pour les boutons
                    //Bouton JOUER
                    if(inMenu){
                        if(mouse_x > 355 && mouse_x < 750 && mouse_y > 302 && mouse_y < 358){
                            isMouseOnPlay = SDL_TRUE;
                        }else{
                            isMouseOnPlay = SDL_FALSE;
                        }
                    }
                    //Bouton QUITTER
                    if(inMenu){
                        if(mouse_x > 357 && mouse_x < 755 && mouse_y > 378 && mouse_y < 437){
                            isMouseOnQuit = SDL_TRUE;
                        }else{
                            isMouseOnQuit = SDL_FALSE;
                        }
                    }
                    if(inMenu){
                        if(mouse_x > 357 && mouse_x < 755 && mouse_y > 455 && mouse_y < 510){
                            isMouseOnAdd = SDL_TRUE;
                        }else{
                            isMouseOnAdd = SDL_FALSE;
                        }
                    }
                    break;
                //Clic de la souris
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                    //clique gauche
                    case SDL_BUTTON_LEFT:
                        if(isMouseOnQuit){ // Si bouton quitter
                            inMenu = SDL_FALSE;
                            program_launched = SDL_FALSE;
                        }
                        if(isMouseOnPlay && !inGame && !askPseudo){ // Si bouton jouer
                            inMenu = SDL_FALSE;
                            inGame = SDL_TRUE;                            
                            }
                        if(isMouseOnAdd && !inGame && !askPseudo){ // Si bouton ajouter
                            inMenu = SDL_FALSE;
                            inGame = SDL_FALSE;
                            addWord = SDL_TRUE;                                
                            }
                        break;
                    
                    }
                
                break;
                case SDL_TEXTINPUT: //pour taper du texte directement
                if(askPseudo){
                    if(textInput[0] == ' '){
                        textInput[0] = '\0';
                    }
                        strcat(textInput, event.text.text);
                        displayTxt(window->sdl_window, window->renderer,"font/absender1.ttf", 50, textInput, PSEUDO_X, PSEUDO_Y);
                        printf("text input: %s\n", textInput);
               }
                break;
                case SDL_KEYDOWN: // pour les touches du clavier
                    switch (event.key.keysym.sym)
                    {   
                        case SDLK_RETURN: //touche entrer
                        
                            if(askPseudo){
                                pseudo = textInput;
                                strToLower(textInput, pseudo); //mettre le pseudo en minuscule
                                printf("pseudo:%s\n", pseudo);
                                askPseudo = SDL_FALSE;
                                inMenu = SDL_TRUE;
                            }
                            continue;
                        case SDLK_BACKSPACE: //touche effacer
                            if(askPseudo){    
                                if(textInput[0] != ' '){
                                    if(strlen(textInput) > 1){
                                        textInput[strlen(textInput)-1] = '\0';
                                        SDL_RenderClear(window->renderer);
                                        displayImg(window->sdl_window, window->renderer, "img/askPseudo.png", 0, 0);
                                        displayTxt(window->sdl_window, window->renderer,"font/absender1.ttf", 50, textInput, PSEUDO_X, PSEUDO_Y);

                                    }else{
                                        textInput[0] = ' ';
                                        SDL_RenderClear(window->renderer);
                                        displayImg(window->sdl_window, window->renderer, "img/askPseudo.png", 0, 0);
                                        displayTxt(window->sdl_window, window->renderer,"font/absender1.ttf", 50, textInput, PSEUDO_X, PSEUDO_Y);
                                    }
                                }
                            }
                        continue;
                        case SDLK_ESCAPE: //touche echap
                            if(inMenu){
                                inMenu = SDL_FALSE;
                                program_launched = SDL_FALSE;
                            }else if(inGame){
                                inMenu = SDL_TRUE;
                                inGame = SDL_FALSE;
                            }
                        break;
                        default:
                            if(inGame){
                                printf("in game\n");
                                keyPressed = event.key.keysym.sym;
                                keyPressed = toupper(keyPressed);
                                printf("You have pressed %c\n", keyPressed);
                            }
                            if(inMenu){
                                printf("in menu\n");
                                keyPressed = event.key.keysym.sym;
                                keyPressed = toupper(keyPressed);
                            }
                        continue;
                        }
         
                case SDL_QUIT:  //Si on clique sur la croix quitter
                    program_launched = SDL_FALSE;
                    break;

                default:
                        if(inMenu){ //si on est dans le menu
                            menu(window->sdl_window, window->renderer,keyPressed,&program_launched,played,won,lose);
                        }else if(inGame){ //si on est dans le jeu
                            game(window->sdl_window, window->renderer,keyPressed,&inGame,&inMenu,played,won,lose);
                        }else if(addWord){ //si on est dans l'ajout de mot
                            addWordMenu(window->sdl_window, window->renderer,&addWord,&inMenu);
                        }
                break;
            }
            
        }
    //}
    free(played);
    free(won);
    free(lose);
    //free(textInput);
    free(pseudo);
    SDL_StopTextInput();
    destroy_window(window);
    TTF_Quit();
    SDL_Quit(); //Libérer la mémoire

    return 0;
}