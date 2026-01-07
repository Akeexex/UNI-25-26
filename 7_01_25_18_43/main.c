#include <stdio.h>
#include <stdlib.h>

typedef struct nd {
    int num;
    struct nd* prev;
    struct nd* next;
}node;

void carica_l(node**);
void vis_l(node**);
void lib_l(node**);
void sort(node**);

int main(void) {
    node* head=NULL;
    int scelta = 0;
    while (scelta!=2) {
        printf("Vuoi caricare un elemento?\n");
        printf("1 - Sì\n");
        printf("2 - No\n");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1:
                carica_l(&head);
                break;
            case 2:
                if (head == NULL) return 0;
                vis_l(&head);
                lib_l(&head);
                break;
            default:
                printf("Inserisci 1 o 2\n");
        }

    }
    return 0;
}

void carica_l(node** h) {
    if (*h == NULL) {
        *h = malloc(sizeof(node));
        if (*h == NULL) {
            printf("Errore malloc");
            exit(1);
        }
        printf("Carica elemento: ");
        scanf("%d", &(*h)->num);
        (*h)->next = NULL;
        (*h)->prev = NULL;
    }
    else {
        sort(h);
        vis_l(h);
    }
}

void vis_l(node** h) {
    node* tmp = *h;
    printf("Lista:");
    while (tmp!=NULL) {
        printf(" %d", tmp->num);
        tmp = tmp->next;
    }
    printf("\n\n");
}

void lib_l(node** h) {
    node* tmp = *h;
    while (tmp!=NULL) {
        tmp = tmp->next;
        free(*h);
        *h = tmp;
    }
    *h = NULL;
}

void sort(node** h) {
    int n;
    printf("Carica elemento: ");
    scanf("%d", &n);
    node* tmp = *h;
    node* tmprec = *h;
    node *new;
    while (tmp!=NULL) {
        if (n > tmp->num) {
            tmprec = tmp;
            tmp = tmp->next;
            if (tmp == NULL) {
                new = malloc(sizeof(node));
                if (new == NULL) {
                    printf("Errore malloc");
                    exit(1);
                }
                new->prev = tmprec;
                tmprec->next = new;
                new->next = NULL;
                new->num = n;
                break;
            }
            continue;
        }
        if (tmp == *h) {
            new = malloc(sizeof(node));
            if (new == NULL) {
                printf("Errore malloc");
                exit(1);
            }
            *h = new;
            (*h)->next = tmp;
            (*h)->prev = NULL;
            (*h)->num = n;
            tmp->prev = *h;
            break;
        }
        new = malloc(sizeof(node));
        if (new == NULL) {
            printf("Errore malloc");
            exit(1);
        }
        tmprec->next = new;
        new->prev = tmprec;
        new->next = tmp;
        tmp->prev = new;
        new->num = n;
        break;
    }
}