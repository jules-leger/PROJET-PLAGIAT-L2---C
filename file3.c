#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;


Cell *add_line(Cell *debut, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = debut;
    return c;
}


void affiche(Cell *debut) {
    Cell *temp = debut;
    while (temp) {
        printf("%s\n", temp->line);
        temp = temp->next;
    }
}

void free_list(Cell *debut) {
    Cell *temp;
    while (debut != NULL) {
        temp = debut;
        debut = debut->next;
        free(temp->line);
        free(temp);
    }
}
void supprime_com(Cell *debut) {
    Cell *cmpt = debut;
    while (cmpt) {
        char *line = cmpt->line;
        int len = strlen(line);
        for (int i = 0; i < len; i++) {
            if (line[i] == '/' && line[i+1] == '/') {
                line[i] = '\0';
                break;
            }
        }
        cmpt = cmpt->next;
    }
}

void Pre_Traitement(const char *filename, int file_number){ 
    //*filename est le nom du fichier et file_number son indice
    // ex: Pre_traitement(argv[1], 1)

    Cell *debut = NULL;

    FILE* f = fopen(filename, "r"); // Ouvre le fichier en mode lecture
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return;
    }


    // Allouer de la mémoire pour la ligne
    char *line = NULL;
    int size = 10;
    line = malloc(sizeof(char)*size);

    while (fgets(line, size, f) != NULL) {
        // On calcule la longueur de la ligne lue
        int len = strlen(line);
        // Tant que la ligne n'a pas été lue entièrement :
        while (line[len - 1] != '\0' && line[len - 1] != '\n') {
            size = size+10; // ajouter 10 à la mémoire allouée
            line = (char *) realloc(line, size);
            if (line == NULL) {
                printf("Erreur d'allocation mémoire");
                return;
            }
            // relire la ligne en repartant de là où on en étais mais avec une mémoire plus grande
            if (fgets(line + len, size - len, f)){
                len = strlen(line);
            }
            // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
            else {
                len++;
                line[len] = '\0';
                debut = add_line(debut, line);
                line = malloc(sizeof(char)*size);
                break;
            }
        }
        //On enlève le \n et on remplace par \0
        line[len - 1] = '\0';
        len--;
        debut = add_line(debut, line);
        line = malloc(sizeof(char)*size);
    }

    if (fclose(f)){
        printf("erreur dans la fermeture du fichier\n");
    }

    // Libérer la mémoire allouée pour la ligne
    free(line);

    // Affiche les lignes de la liste chaînée pour vérifier qu'elles ont été ajoutées correctement
    affiche(debut);

    free_list(debut);
}


    


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  Pre_Traitement(argv[1], 1);
  Pre_Traitement(argv[2], 2);

return 0;
}
