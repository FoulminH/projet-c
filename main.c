#include "fonction.h"

int tentative;


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
	char lettreProposer[tentative+1];

	// Gneration d'un mot
	GenMot(fichier,motSecret);
		if (strlen(motSecret) > 0) {
			InitialChaine(lettreProposer,'0',tentative+1);
			InitialChaine(motActuel,'*',strlen(motSecret));
			printf("Le mot a trouver : %s \nTentatives : %d\n",motActuel,tentative );

			do {
				printf("Donnez une lettre : \n");
				lettre = Norme();
				
				printf("%c \n", lettre);
				// Si la lettre comprise entre A et Z
				if ( !(lettre < 'A') || (lettre > 'Z')) {
					
					// Si la lettre n'est pas le mot actuel et n'a pas été proposée
					if (!LettreUtilise(lettre,motActuel) && !LettreUtilise(lettre,lettreProposer)){
						
						if (LettreUtilise(lettre,motSecret)) {
						printf("la lettre existe !\n");
						int i = 0;
							
							do {
								if (CompareChar(lettre,motSecret[i])) motActuel[i] = motSecret[i];
								i++;
							} while(motSecret[i] != '\0');
							printf("%s\n",motActuel);

						} else {
							tentative--;
							printf("La lettre n'est pas dans le mot \nMot a trouver : %s\nTentative restante : %d\n",motActuel,tentative);
							PlacerCar(lettre,lettreProposer);
						}

					} else {
						printf("Déjà proposé\n");
					}

				} else {
					printf("Ce n'est pas une lettre\nMot a trouver : %s\nTentatives restantes : %d\n",motActuel,tentative);
				}

			}while ((!CompareChaine(motActuel,motSecret)) && (tentative != 0));

			if (tentative == 0) {

				printf("Perdu\n");
				printf("Le bon mot est : %s\n",motSecret);
			}

			else{
				printf("Gagné\n");
				printf("Avec encore %d tentative e stock\n",tentative);
			}

		}

		//si il n'y a pas de mot trouvé
		else{
			printf("Liste de mots introuvable !\n");
		}



  	return 0;
}

