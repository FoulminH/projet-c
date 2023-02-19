#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "sql2.h"

int main(int argc, const char* argv[]){

char* pseudo = malloc(sizeof(char));

pseudo="kevin";

char* played = malloc(sizeof(char));

played = recup_played(pseudo);

printf("%s", played);

char* won = malloc(sizeof(char));

won = recup_win(pseudo);

printf("%s", won);

char* lose = malloc(sizeof(char));

lose = recup_lose(pseudo);

printf("%s", lose);

free(played);
free(lose);
free(won);

return EXIT_SUCCESS;



}


