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

//----------------------------------------------------
// LISTE CHAINÉE
//----------------------------------------------------

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
        printf(" %d /", list->value);
        list = list->next;
    }
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
