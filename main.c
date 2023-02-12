#include "fonction.h"

int tentative;

typedef struct Node Node;
struct Node
{
    int value;
    Node *next;
};

int main(int argc, char const *argv[]) {
	
	printf("Menu Pendu\n");
	FILE* fichier = NULL;
	srand(time(NULL));
	char motSecret[15]={0};
	char motActuel[15]={0};
	char lettre;
	int tentative = 10;

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

	//nb lettre a propser
	//char lettreProposer[tentative+1];

	// Gneration d'un mot
	GenMot(fichier,motSecret);
		if (strlen(motSecret) > 0) {

			//Liste chainée pour stocker le code ASCII des lettre proposées
			Node *list = malloc(sizeof(Node));
			list->value = 0;
			list->next = NULL; 
			
			//création de la chaine secrete
			InitialChaine(motActuel,'*',strlen(motSecret));
			printf("Le mot a trouver : %s \nTentatives : %d\n",motActuel,tentative );

			do {
				printf("Donnez une lettre : \n");
				lettre = Norme();
				
				//printf("%c \n", lettre);

				//printf("%d\n", search_value(list,lettre));

				// Si la lettre comprise entre A et Z
				if ( !(lettre < 'A') || (lettre > 'Z')) {
					
					// Si la lettre n'est pas encore dans le mot actuel et n'a pas encore été proposée
					if (!LettreUtilise(lettre,motActuel) && search_value(list,lettre)==0){
						
						// si la lettre nest dans le mot actuel
						if (LettreUtilise(lettre,motSecret)) {
						printf("la lettre existe !\n");
						
						int i = 0;
							
							do {
								if (CompareChar(lettre,motSecret[i])) motActuel[i] = motSecret[i];
								i++;
							} while(motSecret[i] != '\0');
							printf("%s\n",motActuel);

						// Sinon la mettre dans la liste chainé de stockage des lettres proposé
						} else {
							tentative--;
							printf("La lettre n'est pas dans le mot \nMot a trouver : %s\nTentative restante : %d\n",motActuel,tentative);
							add_to_end(list,lettre);
							//display(list);
						}

					} else {
						printf("Déjà proposé\n");
					}

				} else {
					printf("Ce n'est pas une lettre\nMot a trouver : %s\nTentatives restantes : %d\n",motActuel,tentative);
				}

			} while ((!CompareChaine(motActuel,motSecret)) && (tentative != 0));

			if (tentative == 0) {

				printf("Perdu\n");
				printf("Le bon mot est : %s\n",motSecret);
			}

			else{
				printf("Gagné\n");
				printf("Avec encore %d tentatives en stock\n",tentative);
			}

			free_list(list);

		}

		//si il n'y a pas de mot trouvé
		else{
			printf("Liste de mots introuvable !\n");
		}



  	return 0;
}

