#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "sql2.h"


void add_joueurs(char* pseudo) {
    sqlite3 *db;
    char *erreur = 0;
    int rc;

    // Ouvrir la base de données
    rc = sqlite3_open("db2.db", &db);
    if (rc) {
        fprintf(stderr, "Erreur : impossible d'ouvrir la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }

    // Ajouter le nom d'un joueur dans la table
    char* sql_pseudo = "INSERT INTO joueurs (";

    strcat(sql_pseudo, pseudo);
     
    strcat(sql_pseudo, ") VALUES (?)");
    
    char *sql = sql_pseudo;
    
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erreur : impossible de préparer la requête : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
    sqlite3_bind_text(stmt, 1, pseudo, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erreur : impossible d'exécuter la requête : %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        exit(1);
    }
    sqlite3_finalize(stmt);

    // Fermer la base de données
    sqlite3_close(db);

    printf("Le nom du joueur a été ajouté avec succès.\n");

}



char* recup_played(char* pseudo) {
printf("test");
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char* played = malloc(sizeof(char));
    char* sql_pseudo = malloc(sizeof(char));
    
    printf("test");

    rc = sqlite3_open("db2.db", &db); // ouverture de la base de données
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Impossible d'ouvrir la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return "error";
    }

sql_pseudo = "SELECT parties FROM joueurs WHERE pseudo=";

strcat(sql_pseudo, pseudo);

    char* sql = sql_pseudo; // requête SQL pour récupérer la colonne
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0); // préparation de la requête SQL
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Impossible de préparer la requête SQL : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return "error";
    }
    
played = (char*) sqlite3_column_text(stmt, 0); // récupération de la valeur de la colonne

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erreur lors du parcours des résultats : %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt); // libération des ressources
    sqlite3_close(db);

    return played;
    
    free(played);
}

char* recup_win(char* pseudo) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char* win = malloc(sizeof(char));
    char* sql_pseudo = malloc(sizeof(char));

    rc = sqlite3_open("db2.db", &db); // ouverture de la base de données
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Impossible d'ouvrir la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return "error";
    }

sql_pseudo = "SELECT win FROM joueurs WHERE pseudo=";

strcat(sql_pseudo, pseudo);

    char* sql = sql_pseudo; // requête SQL pour récupérer la colonne
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0); // préparation de la requête SQL
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Impossible de préparer la requête SQL : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return "error";
    }
    
win = (char*) sqlite3_column_text(stmt, 0); // récupération de la valeur de la colonne

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erreur lors du parcours des résultats : %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt); // libération des ressources
    sqlite3_close(db);

    return win;
    
    free(win);
}

char* recup_lose(char* pseudo) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char* lose = malloc(sizeof(char));
    char* sql_pseudo = malloc(sizeof(char));

    rc = sqlite3_open("db2.db", &db); // ouverture de la base de données
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Impossible d'ouvrir la base de données : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return "error";
    }

sql_pseudo = "SELECT loose FROM joueurs WHERE pseudo=";

strcat(sql_pseudo, pseudo);

    char* sql = sql_pseudo; // requête SQL pour récupérer la colonne
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0); // préparation de la requête SQL
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Impossible de préparer la requête SQL : %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return "error";
    }
    
lose = (char*) sqlite3_column_text(stmt, 0); // récupération de la valeur de la colonne

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Erreur lors du parcours des résultats : %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt); // libération des ressources
    sqlite3_close(db);

    return lose;
    
    free(lose);
}

