/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>*/
#include <stdio.h>
#include <stdlib.h>
#include "includes/functions.h"

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
    SDL_bool inGame = SDL_FALSE;

    SDL_Event event;

    //lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0) // Initialisation de la SDL & gestion des erreurs
    {
        SDL_ExitWithError("Initialisation SDL :(");
    }

    if(TTF_Init() != 0){
        TTF_ExitWithError("Initialisation TTF :(");
    }

    //début du programme
    
    displayImg(window->sdl_window,window->renderer, "img/main-menu.png",0,0);                         
    while(program_launched){
        SDL_WaitEvent(&event);
       
        //while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouse_x,&mouse_y);
                    //check la positino de la souris pour créer l'effet hover
                    if(!inGame){
                        if(mouse_x > 355 && mouse_x < 750 && mouse_y > 302 && mouse_y < 358){
                            
                            isMouseOnPlay = SDL_TRUE;
                        }else{
                            isMouseOnPlay = SDL_FALSE;
                        }
                    }
                    
                    //Bouton QUITTER
                    if(!inGame){
                        if(mouse_x > 357 && mouse_x < 755 && mouse_y > 378 && mouse_y < 437){
                            
                            isMouseOnQuit = SDL_TRUE;
                        }else{
                            isMouseOnQuit = SDL_FALSE;
                        }
                    }else{
                        if(mouse_x > 1100 && mouse_x < 1140 && mouse_y > 0 && mouse_y < 40){
                            
                            isMouseOnQuit = SDL_TRUE;
                    }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button)
                    {
                    case SDL_BUTTON_LEFT:
                        
                        
                        if(isMouseOnQuit){
                            program_launched = SDL_FALSE;
                        }

                        if(isMouseOnPlay && !inGame){
                            inGame = SDL_TRUE;
                            displayImg(window->sdl_window, window->renderer, "img/menu-2.png", 0, 0);
                            displayTxt(window->sdl_window, window->renderer,"font/absender1.ttf",50, "Bienvenue dans le jeu du pendu !", 100,300);
                            displayTxt(window->sdl_window, window->renderer,"font/absender1.ttf",50, "Appuyez sur une touche pour commencer", 100,350);
                            printf("in game\n");
                            }
                        break;
                    
                    }
                
                break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                         program_launched = SDL_FALSE;
                        break;
                        default:
                            //keyPressed = event.key.keysym.sym;
                            //printf("You have pressed %c\n", keyPressed);
                            //displayTxt(window,renderer,"font/absender1.ttf", keyPressed);
                            if(inGame){
                                printf("in game\n");
                                keyPressed = event.key.keysym.sym;
                                keyPressed = toupper(keyPressed);
                                printf("You have pressed %c\n", keyPressed);
                                //game(window->sdl_window,window->renderer,keyPressed);
                                //displayImg(window->sdl_window, window->renderer, "img/menu-2.png", 0, 0);
                                
                                game(window->sdl_window, window->renderer,keyPressed,&program_launched);

                            }
                        continue;
                        }
         
                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;

                default:
                /*
                if(inGame){
                    displayImg(window->sdl_window,window->renderer,"img/menu-2.png",0,0); 
                    displayTxt(window->sdl_window, window->renderer,"font/absender1.ttf",50, "Bienvenue dans le jeu du pendu !", 100,300);
                    displayTxt(window->sdl_window, window->renderer,"font/absender1.ttf",50, "Appuyez sur une touche pour commencer", 100,350);

                    //displayImg(window->sdl_window,window->renderer,"img/7.jpg",50,50);   
                    //displayTxt(window->sdl_window,window->renderer,"font/absender1.ttf", 200, "AAAAAAAAAAAA", 100, 50);
                }
            */    
                break;
            }
            
        }
    //}
    destroy_window(window);
    TTF_Quit();
    SDL_Quit(); //Libérer la mémoire

    return 0;
}