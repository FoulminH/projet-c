/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../includes/functions.h"


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



//normaliser les lettre entrée
char Norme(char keyPressed){
  char car = 0;
  car = keyPressed;
  car = toupper(car);
  while (keyPressed != '\n');
  return car;
}

//test d'egalité de caractere
int CompareChar(char c1,char c2){
    if (c1 == c2){ 
      return 1;
    }
    else{ 
      return 0;
    }
}

// test d'egalité de chaine
// retourne 1 si les chaine sont egaux , Sinon return 0
int CompareChaine(char chaine1[],char chaine2[]){ 
  int sortie = 1;
    for (int i = 0; i < ((strlen(chaine1)>strlen(chaine2))?strlen(chaine1):strlen(chaine2)) ;i++){ 
      if (chaine1[i] != chaine2[i]){
        sortie = 0;
      }
    }
    return sortie;
}

// génére un mot alléatoire dans le doc txt "word.txt"
void  GenMot(FILE *fichier,char chaine[]){

    int i = 0;
    int MIN = 1;
    int MAX;
    char x;

    fichier = fopen("word.txt","r");
    if (fichier != NULL)
    {
      while ((x = fgetc(fichier)) != EOF)
      {
          if (x == '\n') {
            i++;
          }
      }
      MAX = i;
      rewind(fichier);
      int line = (rand() % (MAX - MIN + 1)) + MIN; //line aléatoire
      if (line == 1) rewind(fichier);
      else
      {
      while (line - 2 >= 0)
      {
          x = fgetc(fichier);
          if (x == '\n')
          line--;
      }
      }
      fgets(chaine,15,fichier);
      chaine[strlen(chaine)-1] = '\0';
      fclose(fichier);
    } 
    else{
      printf("Erreur fichier txt\n");
    }
}

//initialise une chaine avec nb fois le caractere c
void InitialChaine(char chaine[],char c,int nb){
    int i = 0;
    while (i < nb)
    {
        chaine[i] = c;
        i++;
    }
    chaine[nb] = '\0';
}

//Oui ou non le caractere c est dans la chaine
int LettreUtilise(char c,char chaine[]){
  int i;

  for (i = 0; (c != chaine[i]) && (chaine[i] != '\0') ;i++);
  
  if (chaine[i] != '\0'){ 
    return 1;
  } else {
    return 0;
  }
  
}

//ajouter une lettre a la fin
void PlacerCar(char c,char chaine[]){
  int i;
    for (i=0; chaine[i] != '0' ;i++){
      chaine[i] = c;
    }
}


////////////////////////////////////////////////////////////


void displayPendu(SDL_Window *window, SDL_Renderer *renderer, int tentative){
    int rect_x = 800;
    int rect_y = 600;

    switch(tentative){
        case 7:
            displayImg(window, renderer, "img/0.jpg", rect_x, rect_y);
            break;
        case 6:
            displayImg(window, renderer, "img/1.jpg", rect_x, rect_y);
            break;
        case 5:
            displayImg(window, renderer, "img/2.jpg", rect_x, rect_y);
            break;
        case 4:
            displayImg(window, renderer, "img/3.jpg", rect_x, rect_y);
            break;
        case 3:
            displayImg(window, renderer, "img/4.jpg", rect_x, rect_y);
            break;
        case 2:
            displayImg(window, renderer, "img/5.jpg", rect_x, rect_y);
            break;
        case 1:
            displayImg(window, renderer, "img/6.jpg", rect_x, rect_y);
            break;
        case 0:
            displayImg(window, renderer, "img/7.jpg", rect_x, rect_y);
            break;

    }

}

void quit_game(SDL_bool *program_launched){
    *program_launched = SDL_FALSE;
}


char proposition(SDL_bool *program_launched)
{
    SDL_Event event;
    char choix ;
    while(1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {

            case SDL_QUIT:
                exit(EXIT_FAILURE);
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        //FAIRE QUITTER LE PROG
                        //*program_launched = SDL_FALSE;
                        quit_game(program_launched);
                    break;

                    default:
                    choix = event.key.keysym.sym;
                    return choix;
                }

            case SDL_MOUSEMOTION:
                

        }
    }

}


void game(SDL_Window *window, SDL_Renderer *renderer, char keyPressed, SDL_bool *program_launched){
    FILE* fichier = NULL;
	srand(time(NULL));
	char motSecret[15]={0};
	char motActuel[15]={0};
	char lettre;
	int tentative = 7;
    char* char_tentative = malloc(sizeof(char));
    char_tentative;
    SDL_itoa(tentative, char_tentative, 10);

    //choix difficulté

	/*printf("Choix difficulté :\n");
	printf("1 - facile\n");
	printf("2 - moyen\n");
	printf("3 - difficile\n");
	printf("Mon choix (1, 2 ou 3): ");
	char level = '4';
	
	while (level=='4'){
		level = getchar();
		
		if (level=='1'){
			tentative = 15;
		}
		if (level=='2'){
			tentative = 10;
		}
		if (level=='3'){
			tentative = 5;
		}
		else {
			printf("Erreur choisir 1, 2 ou 3 : ");
		}
		//printf("%d et %d",level, tentative);
		printf("%d \n", tentative);
	} 
*/

	char lettreProposer[tentative+1];
	GenMot(fichier,motSecret);
    if (strlen(motSecret) > 0) {
			InitialChaine(lettreProposer,'0',tentative+1);
			InitialChaine(motActuel,'*',strlen(motSecret));
			//printf("Le mot a trouver : %s \nTentatives : %d\n",motActuel,tentative );
            SDL_RenderClear(renderer);
            displayImg(window, renderer, "img/menu-2.png", 0, 0);
            displayTxt(window, renderer,"font/absender1.ttf",50, "Tentatives : ", 50,50);
            displayTxt(window, renderer,"font/absender1.ttf",50, char_tentative, 350,50);
            displayTxt(window, renderer,"font/absender1.ttf",150, motActuel, 400,200);
            printf("%s\n",motActuel);
            printf("%s\n",motSecret);
            
    do {
				//printf("Donnez une lettre : \n");
				lettre = toupper(proposition(program_launched));
                /*if(lettre == '\b'){
                    printf("QUIT\n");
                    quit_game(program_launched);
                }*/
				printf("%c \n", lettre);
				//printf("%c \n", lettre);
				// Si la lettre comprise entre A et Z
				if ( !(lettre < 'A') || (lettre > 'Z')) {
					
					// Si la lettre n'est pas le mot actuel et n'a pas été proposée
					if (!LettreUtilise(lettre,motActuel) && !LettreUtilise(lettre,lettreProposer)){
						
                        // Si la lettre est dans le mot
						if (LettreUtilise(lettre,motSecret)) {
						printf("la lettre existe !\n");
                            int i = 0;
                                
                                do {
                                    if (CompareChar(lettre,motSecret[i])) motActuel[i] = motSecret[i];
                                    i++;
                                } while(motSecret[i] != '\0');
                                //printf("%s\n",motActuel);
                                
                                SDL_RenderClear(renderer);
                                displayImg(window,renderer,"img/menu-2.png",0,0);                     
                                displayTxt(window, renderer,"font/absender1.ttf",50, "Tentatives : ", 50,50);
                                displayTxt(window, renderer,"font/absender1.ttf",50, char_tentative, 350,50); 
                                displayTxt(window, renderer,"font/absender1.ttf",150, motActuel, 400,200);
                                displayPendu(window, renderer, tentative);

						} else {
							tentative--;
                            SDL_itoa(tentative, char_tentative, 10);
                            SDL_RenderClear(renderer);
                            displayImg(window,renderer,"img/menu-2.png",0,0);                     
                            displayTxt(window, renderer,"font/absender1.ttf",50, "Tentatives : ", 50,50);
                            displayTxt(window, renderer,"font/absender1.ttf",50, char_tentative, 350,50); 
                            displayTxt(window, renderer,"font/absender1.ttf",150, motActuel, 400,200);
                            displayPendu(window, renderer, tentative);
							//printf("La lettre n'est pas dans le mot \nMot a trouver : %s\nTentative restante : %d\n",motActuel,tentative);
                            //Dessiner le pendu
							PlacerCar(lettre,lettreProposer);
						}

					} else {
						//printf("Déjà proposé\n");
					}

				} else {
					//printf("Ce n'est pas une lettre\nMot a trouver : %s\nTentatives restantes : %d\n",motActuel,tentative);
				}

			}while ((!CompareChaine(motActuel,motSecret)) && (tentative > 0));

			if (tentative == 0) {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderClear(renderer);
                displayTxt(window, renderer,"font/absender1.ttf",150, "Perdu !", 400,200);

				//printf("Perdu\n");
				//printf("Le bon mot est : %s\n",motSecret);
			}

			else{
                SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderClear(renderer);
                displayTxt(window, renderer,"font/absender1.ttf",150, "Gagne !", 400,200);

				//printf("Gagné\n");
				//printf("Avec encore %d tentative e stock\n",tentative);
			}

		}

		//si il n'y a pas de mot trouvé
		else{
			//printf("Liste de mots introuvable !\n");
		}
    


}
