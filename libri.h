#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lista_studenti.h"

typedef struct libri{
	char titolo[200];
	char autore[200];
	char isbn[50];
	char stato[30];
	struct libri *sx;
	struct libri *dx;
}Libreria;

bool nodo_vuoto(Libreria *);
Libreria *costruisci_nodo(char [], char [], char [], char []);
Libreria *inserisci_libro(Libreria *, char [], char [], char []);
void salva_su_file(Libreria *);
void salva_su_file_libri_prestati(Libreria *);
Libreria *leggi_da_file(Libreria *);
Libreria *leggi_da_libreria(Libreria *);
Libreria *leggi_da_libreria_prestiti(Libreria *);
Libreria *inserisci_libro_da_file(Libreria *, char [], char [], char [], char []);
void stampa_libreria(Libreria *);
int verifica_se_prestato(char[],int);
Libreria *dealloca_libreria(Libreria *);
int ricerca_libro_per_titolo(Libreria *, Studenti *, char [], int);
int ricerca_libro_per_isbn(Studenti *, char [], int);
void salva_su_file_libri_prestiti_sospesi(char []);
void salva_su_file_libri_inesistenti(char []);
void salva_su_file_libri_prestati1(char [], char [], char []);
char estrai_autore(Libreria *, char [], char []);
char pulisci_buff(char []);
char estrai_isbn(Libreria *, char [], char []);
int elimina_da_biblioteca(char [], char [], int);
int verifica_elimina(char [],char [], int);
void salva_per_elimina(Libreria *);
Libreria *inserisci_libro_per_elimina(Libreria *, char [], char[], char[]);
void salva(FILE *, Libreria *);
