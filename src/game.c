#include "../includes/game.h"

char* strToLower(char* str1, char* str2){
    for (int i = 0; str1[i] != '\0'; i++) {
        str2[i] = tolower(str1[i]);
    }
    return str2;
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

void quit_game(SDL_bool *inGame, SDL_bool *inMenu){
    *inGame = SDL_FALSE;
    *inMenu = SDL_TRUE;
    printf("Vous avez quitter le jeu\n");
}

char proposition(SDL_bool *inGame, SDL_bool *inMenu, int tentative)
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
                        tentative = 0;
                        quit_game(inGame, inMenu);
                    break;

                    default:
                    choix = event.key.keysym.sym;
                    return choix;
                }

            //case SDL_MOUSEMOTION:
                

        }
    }

}


//liste chainée

typedef struct Node Node;
struct Node
{
    char value;
    Node *next;
};

void add_to_end(Node *n, int value)
{
    // naviguer vers la fin de la liste
    while (n->next)
    {
        n = n->next;
    }

    // y allouer un nouveau node
    n->next = malloc(sizeof(Node));
    n->next->next = NULL;
    // donner une valeur au nouveau node
    n->next->value = value;
}



Node *search_value(Node *n, int value)
{
    // naviguer vers le premier noeud qui a la valeur recherchée
    while (n->value != value && n->next)
    {
        n = n->next;
    }

    // verifier qu'il a été trouvé
    if (n->value == value)
    {
        // si le noeud est trouvé, le retourner
        return n;
    }
    else
    {
        // si le noeud est pas trouvé, renvoyer un pointeur NULL
        return NULL;
    }
}

void display(Node *list)
{
    // boucler sur tous les noeuds de la liste
    while (list)
    {
        // afficher le noeud courrant
        printf(" %d \n", list->value);
        list = list->next;
    }
}

void display_used_letter(Node *list, SDL_Window *window, SDL_Renderer *renderer)
{
    //char* char_used_letter = malloc(sizeof(char));
    int c = 0;
    // boucler sur tous les noeuds de la liste
    int i = 0;
    while (list)
    {
        
        // afficher le noeud courrant
        c = list->value;
        list = list->next;
        i++;
    }
    printf("%c\n", c);
}

void free_list(Node *n)
{
    while (n)
    {
        Node *temp = n;
        n = n->next;

        free(temp);
    }
}



void game(SDL_Window *window, SDL_Renderer *renderer, char keyPressed, SDL_bool *inGame, SDL_bool *inMenu){
    FILE* fichier = NULL;
	srand(time(NULL));
	char motSecret[15]={0};
	char motActuel[15]={0};
	char lettre;
	int tentative = 7;
    char* char_tentative = malloc(sizeof(char));
    SDL_itoa(tentative, char_tentative, 10);
    SDL_Event event;
    SDL_bool playing = SDL_TRUE;

    // Generation d'un mot
	GenMot(fichier,motSecret);
    if (strlen(motSecret) > 0) {

        //Liste chainée pour stocker le code ASCII des lettre proposées
        Node *list = malloc(sizeof(Node));
			list->value = 0;
			list->next = NULL; 

			InitialChaine(motActuel,'*',strlen(motSecret));
			//printf("Le mot a trouver : %s \nTentatives : %d\n",motActuel,tentative );
            SDL_RenderClear(renderer);
            displayImg(window, renderer, "img/menu-2.png", 0, 0);
            displayTxt(window, renderer,"font/absender1.ttf",TENTATIVE_SIZE, "Tentatives : ", TXT_TENTATIVE_X,TXT_TENTATIVE_Y);
            displayTxt(window, renderer,"font/absender1.ttf",TENTATIVE_SIZE, char_tentative, INT_TENTATIVE_X,INT_TENTATIVE_Y);
            displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE, motActuel, ACTUAL_WORD_X,ACTUAL_WORD_Y);
            printf("%s\n",motActuel);
            printf("%s\n",motSecret);
            
    do {
				//printf("Donnez une lettre : \n");
				lettre = toupper(proposition(inGame, inMenu, tentative));
                /*if(lettre == '\b'){
                    printf("QUIT\n");
                    quit_game(program_launched);
                }*/
				printf("%c \n", lettre);
				//printf("%c \n", lettre);
				// Si la lettre comprise entre A et Z
				if ( !(lettre < 'A') || (lettre > 'Z')) {
					
					// Si la lettre n'est pas le mot actuel et n'a pas été proposée
					if (!LettreUtilise(lettre,motActuel) && search_value(list,lettre)==0){
						
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
                                displayTxt(window, renderer,"font/absender1.ttf",TENTATIVE_SIZE, "Tentatives : ", TXT_TENTATIVE_X,TXT_TENTATIVE_Y);
                                displayTxt(window, renderer,"font/absender1.ttf",TENTATIVE_SIZE, char_tentative, INT_TENTATIVE_X,INT_TENTATIVE_Y); 
                                displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE, motActuel, ACTUAL_WORD_X,ACTUAL_WORD_Y);
                                displayPendu(window, renderer, tentative);

						} else {
							tentative--;
                            SDL_itoa(tentative, char_tentative, 10);
                            SDL_RenderClear(renderer);
                            displayImg(window,renderer,"img/menu-2.png",0,0);                     
                            displayTxt(window, renderer,"font/absender1.ttf",TENTATIVE_SIZE, "Tentatives : ", TXT_TENTATIVE_X,TXT_TENTATIVE_Y);
                            displayTxt(window, renderer,"font/absender1.ttf",TENTATIVE_SIZE, char_tentative, INT_TENTATIVE_X,INT_TENTATIVE_Y); 
                            displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE, motActuel, ACTUAL_WORD_X,ACTUAL_WORD_Y);
                            displayPendu(window, renderer, tentative);
							//printf("La lettre n'est pas dans le mot \nMot a trouver : %s\nTentative restante : %d\n",motActuel,tentative);
                            //Dessiner le pendu
							add_to_end(list,lettre);
						}

					} else {
						displayTxt(window, renderer,"font/absender1.ttf",TENTATIVE_SIZE, "Lettre deja proposee !", TXT_TENTATIVE_X,TXT_TENTATIVE_Y+50);
                        //display(list);
                        display_used_letter(list, window, renderer);
					}

				} else {
					//printf("Ce n'est pas une lettre\nMot a trouver : %s\nTentatives restantes : %d\n",motActuel,tentative);
				}

			}while ((!CompareChaine(motActuel,motSecret)) && (tentative > 0));

			if (tentative == 0) {// Perdu
                /*SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderClear(renderer);
                displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE, "Perdu !", ACTUAL_WORD_X,ACTUAL_WORD_Y);
                displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE-50, "Le mot etait :", ACTUAL_WORD_X-100,ACTUAL_WORD_Y+110);
                displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE, motSecret, ACTUAL_WORD_X,ACTUAL_WORD_Y+200);*/
                while (playing)
                {
                    SDL_WaitEvent(&event);
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                    SDL_RenderClear(renderer);
                    displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE, "Perdu !", ACTUAL_WORD_X,ACTUAL_WORD_Y);
                    displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE-50, "Le mot etait :", ACTUAL_WORD_X-100,ACTUAL_WORD_Y+110);
                    displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE, motSecret, ACTUAL_WORD_X,ACTUAL_WORD_Y+200);
                        switch(event.type){
                            case SDL_KEYDOWN: // pour les touches du clavier
                            switch (event.key.keysym.sym)
                            {   case SDLK_ESCAPE:
                                    printf("escape\n");
                                    playing = SDL_FALSE;
                                    quit_game(inGame, inMenu);
                                break;
                                default:
                                    playing = SDL_FALSE;
                                break;
                            }

                            }
                
                }
			}

			else{// Gagné
                while (playing)
                    {
                        SDL_WaitEvent(&event);
                        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
                        SDL_RenderClear(renderer);
                        displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE, "Gagne !", ACTUAL_WORD_X,ACTUAL_WORD_Y);
                        displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE-50, "Le mot etait :", ACTUAL_WORD_X-100,ACTUAL_WORD_Y+110);
                        displayTxt(window, renderer,"font/absender1.ttf",WORD_SIZE, motSecret, ACTUAL_WORD_X,ACTUAL_WORD_Y+200);
                            switch(event.type){
                                case SDL_KEYDOWN: // pour les touches du clavier
                                switch (event.key.keysym.sym)
                                {   
                                    case SDLK_ESCAPE:
                                        printf("escape\n");
                                        playing = SDL_FALSE;
                                        quit_game(inGame, inMenu);
                                    break;
                                    default:
                                        playing = SDL_FALSE;
                                    break;
                                }

                                }
                    
                    }
                

				//printf("Gagné\n");
				//printf("Avec encore %d tentative e stock\n",tentative);
			}
            free_list(list);

		}

		//si il n'y a pas de mot trouvé
		else{
			//printf("Liste de mots introuvable !\n");
		}
    


}


