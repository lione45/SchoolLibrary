#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
    char nome[30];
    char cognome[30];
    char matr[20];
    char titolo[100];
    char autore[100];
    char isbn[20];
    char stato[20];
    struct lista *next;
}Prestiti;

Prestiti *alloca_prestito(char [], char[], char[], char[], char[], char[], char[]);
Prestiti *inseririsci_prestito(Prestiti*, char [], char[], char[], char[], char[], char[], char[]);
Prestiti *dealloca_prestito(Prestiti *);
void salva_su_file_lista_prestiti(Prestiti *);
int restituisci(char [], char [], int);
