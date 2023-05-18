#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista_sos{
    char nome[30];
    char cognome[30];
    char matr[20];
    char titolo[100];
    struct lista_sos *next;
}Prestiti_sos;

Prestiti_sos *alloca_prestito_sos(char [], char[], char[], char[]);
Prestiti_sos *inseririsci_prestito_sos(Prestiti_sos*, char [], char[], char[], char[]);
Prestiti_sos *dealloca_prestito_sos(Prestiti_sos *);
void salva_su_file_lista_prestiti_sos(Prestiti_sos* l);
void rimuovi_da_prestiti_sos(char [], char []);
void salva_su_file_lista_libri_inesistenti(Prestiti_sos* l);
void rimuovi_da_libri_inesistenti(char [], char [], char []);
