#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


typedef struct cellule{
    char *line;
    struct cellule *next;
} Cell;

typedef struct {
    Cell* start;
    int size;
} List;

List *Allocate_List(void){
    List *l=malloc(sizeof(List));
    l->start=NULL;
    l->size=0;
    return l;
}


/* Inserts a new cell at the top of the linked list containing a line from the file.
 Returns the pointer to the new beginning of the list.
 The line is copied before the storage. */

List *add_line(List* l, char *line) {
    Cell *c = malloc(sizeof(Cell));
    c->line = strdup(line);
    c->next = l->start;
    l->start=c;
    l->size++;
    return l;
}


void show_list(List *l) {
    Cell *tmp = l->start;
    while (tmp) {
        printf("%s\n", tmp->line);
        tmp = tmp->next;
    }
}

void free_list(List *l) {
    Cell *tmp;
    while (l->start != NULL) {
        tmp = l->start;
        l->start = l->start->next;
        free(tmp->line);
        free(tmp);
    }
}



void PreTraitement (char *line) {
    int len = strlen(line);
    char *new_line = malloc((len + 1) * sizeof(char));
    if (!new_line) { puts("Erreur d'allocation mémoire"); return; }

    int j = 0;
    for (int i = 0; i < len; i++) {

        // commentaires //
        if (line[i] == '/' && i + 1 < len && line[i+1] == '/') {
            break; // tronque la ligne
        }

        // chaînes "..."
        else if (line[i] == '\"') {
            new_line[j++] = line[i];
            i++;
            while (i < len && line[i] != '\"') { i++; }
            if (i < len) new_line[j++] = line[i]; // fermer si trouvé
        }

        // caractères 'c'
        else if (line[i] == '\'') {
            new_line[j++] = line[i];
            i++;
            while (i < len && line[i] != '\'') { i++; }
            if (i < len) new_line[j++] = line[i];
        }

        // mots -> 'w'
        else if (isalnum((unsigned char)line[i]) || line[i] == '_') {
            while (i + 1 < len && (isalnum((unsigned char)line[i+1]) || line[i+1] == '_')) {
                i++;
            }
            new_line[j++] = 'w';
        }

        // espaces → ignore
        else if (line[i] == ' ') {
            continue;
        }

        // reste
        else {
            new_line[j++] = line[i];
        }
    }

    new_line[j] = '\0';
    strcpy(line, new_line);
    free(new_line);
}




List* Segmentation(const char *filename, List* l){
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Impossible d'ouvrir le fichier %s en lecture.\n", filename);
        return NULL;
    }

    char *line = NULL;
    size_t cap = 0;
    ssize_t n;

    while ((n = getline(&line, &cap, f)) != -1) {
        // retire le '\n' final le cas échéant
        if (n > 0 && line[n-1] == '\n') line[n-1] = '\0';
        PreTraitement(line);
        if (*line) l = add_line(l, line);
    }

    free(line);
    fclose(f);
    return l;
}

typedef struct {
    char digram[3];
    int frequency;
} Digram;

typedef struct {
    Digram* D;
    int size;
} DigramList;


void add_digram(DigramList* list, char* new_digram) {
    // Checks if the digram passed as argument is present in the list.
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->D[i].digram, new_digram) == 0) {
            // increments the frequency of this digram by 1.
            list->D[i].frequency++;
            return;
        }
    }
    // adds this digram to the digram list.
    list->D = realloc(list->D, sizeof(Digram) * (list->size + 1));
    strcpy(list->D[list->size].digram, new_digram);
    list->D[list->size].frequency = 1;
    list->size++;
}

// Creates a list of digrams of the line passed as argument
DigramList* get_D(char* line) {
    DigramList* list = malloc(sizeof(DigramList));
    list->D = NULL;
    list->size = 0;
    for (int i = 0; i < strlen(line) - 1; i++) {
        // call add_digram for each digram of the line
        char new_digram[3] = {line[i], line[i + 1], '\0'};
        add_digram(list, new_digram);
    }
    return list;
}

float Dice(char* line1, char* line2) {

    // Case where a line contains only 1 character:
    if (strlen(line1)==1 && strlen(line2)==1){
        if (strcmp(line1, line2)==0){
            return 0.0;
        }
        return 1.0;
    }

    //Create the digram list of line 1
    DigramList* list1 = get_D(line1); 

    //Create the digram list of line 2
    DigramList* list2 = get_D(line2);

    // Initialise the number of digrams in common to 0
    int intersection = 0; 

    // Browse all digrams in line1 and line2
    for (int i = 0; i < list1->size; i++) {
        for (int j = 0; j < list2->size; j++) {
            // If common digram, the minimum frequency is added (the number of times it is present in the chain of which it is the least present)
            if (strcmp(list1->D[i].digram, list2->D[j].digram) == 0) {
                int min_frequency;
                if (list1->D[i].frequency >= list2->D[j].frequency){
                    min_frequency=list2->D[j].frequency;
                }
                else {
                    min_frequency=list1->D[i].frequency;
                }
                intersection += min_frequency;
                break;
            }
        }
    }
    // denominator = number of digrams in line1 + number of digrams in line2
    int denominator = strlen(line1) + strlen(line2) - 2;

    float dice = 1- (2.0 * intersection / denominator);
    free(list1->D);
    free(list1);
    free(list2->D);
    free(list2);
    return dice;
}

// Bonus : Trigram
//(It is enough to modify in the same way to calculate the other n-grams)

typedef struct {
    char trigram[4];
    int frequency;
} Trigram;

typedef struct {
    Trigram* T;
    int size;
} TrigramList;


void add_trigram(TrigramList* list, char* new_trigram) {
    // Checks if the trigram passed as argument is present in the list.
    for (int i = 0; i < list->size; i++) {
        if (strcmp(list->T[i].trigram, new_trigram) == 0) {
            // increments the frequency of this trigram by 1.
            list->T[i].frequency++;
            return;
        }
    }
    // adds this digram to the digram list.
    list->T = realloc(list->T, sizeof(Trigram) * (list->size + 1));
    strcpy(list->T[list->size].trigram, new_trigram);
    list->T[list->size].frequency = 1;
    list->size++;
}

// Creates a list of digrams of the line passed as argument
TrigramList* get_T(char* line) {
    TrigramList* list = malloc(sizeof(TrigramList));
    list->T = NULL;
    list->size = 0;
    for (int i = 0; i < strlen(line) - 2; i++) {
        // call add_trigram for each trigram of the line
        char new_trigram[4] = {line[i], line[i + 1], line[i + 2], '\0'};
        add_trigram(list, new_trigram);
    }
    return list;
}

float Tri_Dice(char* line1, char* line2) {

    // Cases where a line contains less than 3 characters:
    if (strlen(line1)<=2 || strlen(line2)<=2){
        
        // Cases where they are similar :
        if (strlen(line1)==strlen(line2)){
            if (strcmp(line1, line2)==0){
                return 0.0;
            }   
        }
        return 1.0;
    }
       

    //Create the trigram list of line 1
    TrigramList* list1 = get_T(line1); 

    //Create the trigram list of line 2
    TrigramList* list2 = get_T(line2);

    // Initialise the number of trigrams in common to 0
    int intersection = 0; 

    // Browse all trigrams in line1 and line2
    for (int i = 0; i < list1->size; i++) {
        for (int j = 0; j < list2->size; j++) {
            // If common trigram, the minimum frequency is added (the number of times it is present in the chain of which it is the least present)
            if (strcmp(list1->T[i].trigram, list2->T[j].trigram) == 0) {
                int min_frequency;
                if (list1->T[i].frequency >= list2->T[j].frequency){
                    min_frequency=list2->T[j].frequency;
                }
                else {
                    min_frequency=list1->T[i].frequency;
                }
                intersection += min_frequency;
                break;
            }
        }
    }
    // denominator = number of trigrams in line1 + number of trigrams in line2
    int denominator = strlen(line1) + strlen(line2) - 4;

    float dice = 1- (2.0 * intersection / denominator);
    free(list1->T);
    free(list1);
    free(list2->T);
    free(list2);
    return dice;
}




// filling the matrix D with the distances of Dice    
void matrix (List *l1, List *l2, float* D){
    Cell *tmp1 = l1->start;
    Cell *tmp2 = l2->start;
    for (int i=0; i<l1->size; i++){
        for (int j=0; j<l2->size; j++){
                float dice = Dice(tmp1->line, tmp2->line);
                // float dice = Tri_Dice(tmp1->line, tmp2->line);
                D[i*l2->size+j]=dice;
                tmp2=tmp2->next;
        }
        tmp2 = l2->start;
        tmp1=tmp1->next;
    }
}



void couplage (int size_file1, int size_file2, float* D, float* C) {
    // Initialization of the matrix C to 0
    for (int i = 0; i < size_file1; i++) {
        for (int j = 0; j < size_file2; j++) {
            C[i*size_file2 + j] = 0.0;
        }
    }
    // Loop until there are no more segments to combine in the smallest programme
    for (int k = 0; k < size_file1; k++) {
        // Finding the smallest coefficient of the matrix D
        int i_min = 0, j_min = 0;
        float dice_min = 2;
        for (int i = 0; i < size_file1; i++) {
            for (int j = 0; j < size_file2; j++) {
                if (C[i*size_file2 + j] == 0.0 && D[i*size_file2 + j] < dice_min) {
                    dice_min = D[i*size_file2 + j];
                    i_min = i;
                    j_min = j;
                }
            }
        }
        // Set all coefficients 0 in column j_min and i_min to 1
        for (int p = 0; p < size_file1; p++) {
            if (C[p*size_file2 + j_min]==0.0){
                C[p*size_file2 + j_min] = 1.0;
            }
        }
        for (int q = 0; q < size_file2; q++) {
            if (C[i_min*size_file2 + q]==0.0){
                C[i_min*size_file2 + q] = 1.0;
            }
        }
        // Marking the i_min and j_min segments
        C[i_min*size_file2 + j_min] = 2.0;
    }
    // Put back the distances of Dice associated to the marked segments
    for (int i=0; i<size_file1; i++){
        for (int j=0; j<size_file2; j++){
            if (C[i*size_file2+j]==2.0){
                C[i*size_file2+j]=D[i*size_file2+j];
            }
        }
    }
}

void post_filtrage (int size_file1, int size_file2, float* C, float* F, float* ptr) {

    for (int i=0; i<size_file1; i++){
        for (int j=0; j<size_file2; j++){
            float sum = 0.0;
            int count=0;
            for (int k=-2; k<=2; k++){
                int l=i+k;
                int c=j+k;
                if (l<0 || l>=size_file1 || c<0 || c>=size_file2){
                    continue;
                }
                // we check that the segments exist
                else {
                    sum += C[(i+k)*size_file2+j+k];
                    count++;
                }
            }
            float moyenne = (float)sum/count;
                if(moyenne>=0.7){
                    moyenne=1.0;
                }
            F[i*size_file2+j]=moyenne;
            *ptr+=(1-F[i*size_file2+j]);
        }
    }
    *ptr= 1 - (*ptr/size_file1);
}


void View_Matrix(int file1, int file2, float* M, char* name_file) {
    // Opening the file for writing
    FILE* f = fopen(name_file, "w");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    // Writing header information
    fprintf(f, "P2\n%d %d\n255\n", file2, file1);

    // Writing the values of the matrix
    for (int i = 0; i < file1; i++) {
        for (int j = 0; j < file2; j++) {
            // Conversion of the value to a grey level between 0 and 255
            int grey_shade = (int)((1 - M[i * file2 + j]) * 255);
            fprintf(f, "%d ", grey_shade);
        }
        fprintf(f, "\n");
    }

    // Closing the file
    fclose(f);
}



float distance(char* name_file1, char* name_file2, int i, int j) {

  List *l1 = Allocate_List();
  List *l2 = Allocate_List();
  
  l1 = Segmentation(name_file1, l1);
  l2 = Segmentation(name_file2, l2);
  
  int size_file1 = l1->size;
  int size_file2 = l2->size;

  float delta = 0;

  float *D = (float *) malloc(sizeof(float)*size_file1*size_file2);
  if (D == NULL) {
    printf("Erreur d'allocation de mémoire\n");
    return -1;
  }

  float *C = (float *) malloc(sizeof(float)*size_file1*size_file2);
  if (C == NULL) {
    printf("Erreur d'allocation de mémoire\n");
    return -1;
  }

  float *F = (float *) malloc(sizeof(float)*size_file1*size_file2);
  if (F == NULL) {
    printf("Erreur d'allocation de mémoire\n");
    return -1;
  }

  char filename[25];

  // We make sure that the file with the least number of lines is used for the size of the matrices
  if (size_file1 <= size_file2) {
    matrix (l1, l2, D);
    sprintf(filename, "dice_%d_%d.pgm", i, j);
    View_Matrix(size_file1, size_file2, D, filename);
    couplage (size_file1, size_file2, D, C);
    sprintf(filename, "couplage_%d_%d.pgm", i, j);
    View_Matrix(size_file1, size_file2, C, filename);
    post_filtrage (size_file1, size_file2, C, F, &delta);
    sprintf(filename, "filtrage_%d_%d.pgm", i, j);
    View_Matrix(size_file1, size_file2, F, filename);
  } 
  else {
    matrix (l2, l1, D);
    sprintf(filename, "dice_%d_%d.pgm", i, j);
    View_Matrix(size_file2, size_file1, D, filename);
    couplage (size_file2, size_file1, D, C); 
    sprintf(filename, "couplage_%d_%d.pgm", i, j);
    View_Matrix(size_file2, size_file1, C, filename);
    post_filtrage (size_file2, size_file1, C, F, &delta);
    sprintf(filename, "filtrage_%d_%d.pgm", i, j);
    View_Matrix(size_file2, size_file1, F, filename);
  }

  free(D);
  free(C);
  free(F);
  free_list(l2);
  free_list(l1);
  
  return delta;
}



int main (int argc, char* argv[]) {

  // checks if at least two file names have been given as arguments
  int number_of_file= argc -1;
  if (number_of_file < 2) {
    printf("Utilisation : %s <nom_fichier>\n", argv[0]);
    return 0;
  }

  float *M = (float *) malloc(sizeof(float)*number_of_file*number_of_file);
  if (M == NULL) {
    printf("Erreur d'allocation de mémoire\n");
    return -1;
  }

  for (int i = 0; i < number_of_file; i++) {
    for (int j = i + 1; j < number_of_file; j++) {
      // calculate the distance between files i and j and store it in lenght
      float lenght = distance(argv[i + 1], argv[j + 1], i+1, j+1);
      printf("La distance entre le fichier %d et %d est de : %.2f\n", i+1, j+1, lenght);
      M[i * number_of_file + j] = lenght;
      M[j * number_of_file + i] = lenght;
    }
  }


  View_Matrix(number_of_file,number_of_file, M, "distances.pgm");


 // display the distance matrix
  for (int i = 0; i < number_of_file; i++) {
    for (int j = 0; j < number_of_file; j++) {
      printf("%.2f ", M[i * number_of_file + j]);
    }
    printf("\n");
  }

  return 0;
}
