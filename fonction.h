#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>


char Norme();
int CompareChar(char c1,char c2);
int CompareChaine(char chaine1[],char chaine2[]);
void GenMot(FILE *fichier,char chaine[]);
void InitialChaine(char chaine[],char c,int nb);
int LettreUtilise(char c,char chaine[]);
void PlacerCar(char,char[]);