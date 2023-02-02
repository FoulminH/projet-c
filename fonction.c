#include "fonction.h"

//noramiser les lettre entrée
char Norme(){
  char car = 0;
  car = getchar();
  car = toupper(car);
  while (getchar() != '\n');
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

//initialise une chaine avec x fois le caractere c
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

