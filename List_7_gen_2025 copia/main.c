#include <stdio.h>
#include <stdlib.h>

typedef struct nd {
    int n;
    struct nd* next;
}node;

void carica_l(node**, node**);
void vis_l(node**);
void lib_l(node**, node**);
float media_l(node**);
void ricucisci(node**, float, int*);
void crea_vett(node**, node***, int) ;
void stmp_indx_l(node**);
void stampa_indx(node**, node**, int);

int main(void) {
    node* head=NULL;
    node* tail=NULL;
    node** array;
    int scelta = 0, dim_new = 0;
    float media;
    while (scelta !=2) {
        printf("Vuoi caricare un elemento nella lista?\n");
        printf("1 - Sì\n");
        printf("2 - No\n");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1:
                carica_l(&head, &tail);
                break;

            case 2:
                if (head == NULL) return 0;
                vis_l(&head);
                stmp_indx_l(&head);
                media = media_l(&head);
                ricucisci(&head, media, &dim_new);
                crea_vett(&head, &array, dim_new);
                stampa_indx(&head, array, dim_new);
                lib_l(&head, &tail);
                free(array);
                break;

            default:
                printf("Inserisci un valore 1 o 2\n");

        }
    }

    return 0;
}

void carica_l(node** h, node** t) { //Usiamo doppi puntatori per modificare le variabili nel main
    if (*h == NULL) {
        *h = malloc(sizeof(node));
        if (*h == NULL) { //Check se malloc non restituisce un indirizzo
            printf("Errore malloc\n");
            exit(1);
        }
        printf("Carica elemento: ");
        scanf("%d", &(*h)->n);
        (*h)->next = NULL;
        *t = *h;
    }
    else {
        (*t)->next = malloc(sizeof(node));
        if ((*t)->next == NULL) {
            printf("Errore malloc\n");
            exit(1);
        }
        *t = (*t)->next;
        printf("Carica elemento: ");
        scanf("%d", &(*t)->n);
        (*t)->next = NULL; //La lista deve SEMPRE terminare con NULL
    }
}

void vis_l(node** h) {
    printf("Lista:");
    node* tmp = *h;//Variabile tmp per non perdere la testa della lista
    while (tmp != NULL) { //Se tmp == NULL la lista è terminata
        printf(" %d", tmp->n);
        tmp = tmp->next;
    }
    printf("\n\n");
}

void lib_l(node** h, node** t) {
    node* tmp = *h;
    while (tmp != NULL) {
        tmp = tmp->next;
        free(*h);
        *h = tmp;
    }
    //Quest' ultima parte non è rilevante se il programma termina subito dopo
    *h = NULL;
    *t = NULL;
}

float media_l(node** h) {
    float sum = 0;
    int dim = 0;
    node* tmp = *h;
    while (tmp != NULL) {
        sum += tmp->n;
        dim++;
        tmp = tmp->next;
    }
    return sum / dim;
}

void ricucisci(node** h, float med, int* dim_n) {
    node* tmp_prev = *h;
    node* tmp = *h;
    node* elim;

    while (tmp != NULL) {
        if (tmp->n < med) {
            if (tmp == *h) {
                *h = tmp->next;
                free(tmp);
                tmp = *h;
                tmp_prev = *h;
                continue;
            }
            elim = tmp;
            tmp = tmp->next;
            free(elim);
            tmp_prev->next = tmp;
            continue;
        }
        if (tmp == *h) {
            tmp = tmp->next;
            (*dim_n)++;

        }
        else {
            tmp = tmp->next;
            tmp_prev = tmp_prev->next;
            (*dim_n)++;
        }
    }
}

void crea_vett(node** h, node*** v, int dim_n) {
    *v = calloc(dim_n, sizeof(node*));
    node* tmp = *h;
    for (int i = 0; i < dim_n; i++) {
        (*v)[i] = tmp;
        tmp = tmp->next;
    }
}

void stmp_indx_l(node** h) {
    node* tmp = *h;
    printf("Indirizzi iniziali:\n");
    while (tmp!=NULL) {
        printf("%p\n", tmp);
        tmp = tmp->next;
    }
    printf("\n\n");
}

void stampa_indx(node** h, node** v, int dim) {
    node* tmp = *h;
    printf("Indirizzi finali:\n");
    for (int i = 0; i < dim; i++) {
        printf("%p\n", tmp);
        printf("%p\n\n", v[i]);
        tmp = tmp->next;
    }
}