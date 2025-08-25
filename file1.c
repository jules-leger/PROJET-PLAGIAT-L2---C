//commentaire paraphrasé, nom des variables changé, ordre des fonction modifié

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
char *line;
struct node *next;
} Node;

/* Insère une nouvelle cellule contenant la ligne du fichier au début de la liste des liens.
* Renvoie un pointeur vers la nouvelle tête de liste.
* Les lignes sont copiées avant d'être enregistrées. */

Node *add_text(Node *start, char *line) {
Node *n = malloc(sizeof(Node));
n->line = strdup(line);
n->next = start;
return n;
}

void clear_list(Node *start) {
Node *temp;
while (start != NULL) {
temp = start;
start = start->next;
free(temp->line);
free(temp);
}
}

void display(Node *start) {
Node *temp = start;
while (temp) {
printf("%s\n", temp->line);
temp = temp->next;
}
}

void process_file(const char *file_name, int file_number){
//*filename est le nom du fichier et file_number son indice
Node start = NULL;
FILE file = fopen(file_name, "r"); // le fichier est ouvert en mode lecture
if (!file) {
printf("Unable to open file %s for reading.\n", file_name);
return;
}
 // Allouer de la mémoire pour la ligne
char *line = NULL;
int buffer_size = 10;
line = malloc(sizeof(char)*buffer_size);

while (fgets(line, buffer_size, file) != NULL) {
// On calcule la longueur de la ligne lue
    int len = strlen(line);
    // Tant que la ligne n'a pas été lue entièrement :
    while (line[len - 1] != '\0' && line[len - 1] != '\n') {
        buffer_size = buffer_size + 10;
        line = (char *) realloc(line, buffer_size);
        if (line == NULL) {
            printf("Memory allocation error");
            return;
        }
        // Relisez la ligne, en reprenant là où vous vous étiez arrêté, mais en utilisant plus de mémoire
        if (fgets(line + len, buffer_size - len, file)){
            len = strlen(line);
        }
        // Si fin du fichier, on en est à la dernière ligne qui ne finit pas par \n
        else {
            len++;
            line[len] = '\0';
            start = add_text(start, line);
            line = malloc(sizeof(char)*buffer_size);
            break;
        }
    }
    //On rempalce le \n par \0
    line[len - 1] = '\0';
    len--;
    start = add_text(start, line);
    line = malloc(sizeof(char)*buffer_size);
}

if (fclose(file)){
    printf("error closing file\n");
}
free(line);
}

void remove_comments(Node *start) {
Node *count = start;
while (count) {
    char *line = count->line;
    int len = strlen(line);
    for (int i = 0; i < len; i++) {
        if (line[i] == '/' && line[i+1] == '/') {
            line[i] = '\0';
            break;
        }
    }
    count = count->next;
}
}


int main (int argc, char* argv[]) {
  // vérifie si deux noms de fichiers ont été donné en argument
  if (argc < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }
  process_file(argv[1], 1);
  process_file(argv[2], 2);

return 0;
}
