#include <stdio.h>
#include <stdlib.h>

typedef struct maillon{
    int val;
    struct maillon* suivant;
} Maillon;


typedef struct{
    Maillon* tete;
} Liste;


Maillon *ListeAlloueMaillon(int val){
    Maillon* m=malloc(sizeof(Maillon));
    m->suivant=NULL;
    m->val=val;
    return m;
}

Liste *ListeAlloueListe(void){
    Liste *l=malloc(sizeof(Liste));
    l->tete=NULL;
    return l;
}

void ListeInsereEnTete(Liste *l, int val){
    Maillon *m=ListeAlloueMaillon(val);
    m->suivant=l->tete;
    l->tete=m;
}

void ListeSaisie(Liste *l){
    int n;
    printf("Combien de maillons voulez-vous ajouter ?\n");
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        int val;
        printf("Quelle valeur pour le %dème maillon?\n", i+1);
        scanf("%d", &val);
        ListeInsereEnTete(l, val);
    }
}

void ListeAfficheIt(Liste *l){
    Maillon *m = malloc(sizeof(Maillon));
    m = l->tete;
    printf("Voici les valeurs des maillons:");
    while (m!=NULL){
        printf("%d ", m->val);
        m=m->suivant;
    }

    printf("\n");
    free (m);
}

void ListeAfficheRec(Liste *l){

    if(l->tete!=NULL){
        printf("%d ", l->tete->val);
        l->tete=l->tete->suivant;
        ListeAfficheRec(l);
    }
}

void ListeLecture (Liste *l, FILE* f){
    int c;
    while (1){
        fscanf(f, "%d", &c);
        ListeInsereEnTete(l, c);
        if (feof(f))
            return;
    }
}

void ListeEcritIt (Liste *l, FILE* fOut){

    fOut=fopen("Liste.txt", "w");
    Maillon *m = malloc(sizeof(Maillon));
    m = l->tete;
    fprintf(fOut, "Voici les valeurs des maillons:");
    while (m!=NULL){
        fprintf(fOut, "%d ", m->val);
        m=m->suivant;
    }
    fclose(fOut);
    free(m);
}

Maillon *ListeRecherche (Liste *l, int val){
    Maillon *m = malloc(sizeof(Maillon));
    m = l->tete;
    while (m!=NULL){
        if (m->val==val){
            return m;
        }
        m=m->suivant;
    }
    return NULL;
}

void ListeInsertApres (Liste *l, int val, int ap){
    Maillon *m=ListeAlloueMaillon(val);
    m->suivant= ListeRecherche(l,ap)->suivant;
    ListeRecherche(l,ap)->suivant=m;
}

void ListeConcatenation (Liste *l1, Liste *l2){
    Maillon *m1 = l1->tete;
    Maillon *m2 = l2->tete;
    while (m1->suivant!=NULL){
        m1=m1->suivant;
    }
    while (m2!=NULL){
        m1->suivant=m2;
        m2=m2->suivant;
        m1=m1->suivant;
    }
}

void LibereListe (Liste *l){
    free(l);
}

void Supp1ereOcc (Liste *l, int val){

    Maillon *m= malloc(sizeof(Maillon));
    m=ListeRecherche(l, val);
    if (m==NULL) return;
    m = l->tete;
    if (m->val==val){
        l->tete=m->suivant;
        return;
    }
    while (m!=NULL){
        if (m->suivant->val==val){
            m->suivant=m->suivant->suivant;
            return;
        }
        m=m->suivant;
    }
    free(m);
}

void SuppInf (Liste *l, int val){
    Maillon *m= malloc(sizeof(Maillon));
    m = l->tete;
    while (m->val<val){
        l->tete=m->suivant;
        m = l->tete;
    }
    while (m!=NULL && m->suivant!=NULL){
        if (m->suivant!=NULL && m->suivant->val<val){
            if (m->suivant->suivant==NULL){
                m->suivant=NULL;
            }
            else m->suivant=m->suivant->suivant;
        }
        if (m->suivant!=NULL && m->suivant->val>=val){
            m=m->suivant;
        }
    }
    free(m);

}


int main(){
    
    Liste *l= ListeAlloueListe();
    Liste *l2= ListeAlloueListe();

    FILE* fichier = fopen("maillons.txt", "r");
    if (fichier!=NULL){
        ListeLecture(l, fichier);
        fclose(fichier);
	}
    ListeSaisie(l2);

    ListeAfficheIt(l);
    ListeAfficheIt(l2);

    ListeInsereEnTete(l2, 10);
    ListeAfficheIt(l2);

    ListeConcatenation(l,l2);
    ListeAfficheIt(l);

    SuppInf(l,5);
    ListeAfficheIt(l);

    ListeInsertApres(l,100, 6);
    ListeAfficheIt(l);

    Supp1ereOcc(l,100);
    ListeAfficheIt(l);

    ListeEcritIt(l, fichier);


    LibereListe(l);
    LibereListe(l2);
    return 0;
}


 /* 

    FILE* f = fopen("maillons2.txt", "r");
    if (f!=NULL){
        ListeLecture(l2, f);
        fclose(f);
	} 

    ListeAfficheRec(l);
    
    */
