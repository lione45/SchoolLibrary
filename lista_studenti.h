#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "prestiti.h"
#include "prestiti_sos.h"

typedef struct utente{
	char nome[50];
	char cognome[50];
	char matricola[20];
	struct utente* next;
}Studenti;

Studenti *nuovo_nodo(char [], char [], char []);
Studenti *inserisci_studenti_in_coda(Studenti *);
Studenti *crea_lista_studenti(Studenti *);
void stampa_lista_studenti(Studenti *);
Studenti *dealloca_lista_studenti(Studenti *);
void salva_su_file_utenti_libreria(Studenti *);
void salva_su_file_utenti_prestiti_sospesi(Studenti *);
void salva_su_file_utenti_prestiti_inesistenti(Studenti *);
int verifica_max_prestiti(Studenti *, int);
int verifica_richieste_prestiti(char [], int);
int verifica_richieste_aggiunta_libro(char [],char [], int);
int verifica_Max_prestiti(char[], int);
char estrai_nome(char[], char[]);
char estrai_cognome(char [], char []);
char estrai_matricola(char[], char[]);
char estrai_nome_da_aggiunta(char[], char[]);
char estrai_cognome_da_aggiunta(char [], char []);
char estrai_matricola_da_aggiunta(char[], char [], char[]);
void salva_prestito(char [], char [], char [], char [], char [], char []);
void stampa_prestiti_altri_utenti(Studenti *);
void stampa_prestiti();
void stampa_prestiti_utente_corrente(Studenti *);
int restituisci_corrente(Studenti *, char [], int );
int stato_prestiti(int);
int stato_sospesi(int);
int stato_non_presenti(int);
char pulisci(char []);

