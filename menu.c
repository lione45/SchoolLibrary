#include "menu.h"

int menu_iniziale(int a){
	printf("============ Benvenuto Nel Menu' Della Biblioteca. ============\n");
	printf("===============================================================\n");
	printf(" ____________________________________________________________\n|Scegli Cosa Fare:\t\t\t\t\t     |\n|____________________________________________________________|\n|\t\t\t\t\t\t\t     |\n");
	printf("|1)Servizi Studenti;\t\t\t\t\t     |\n|2)Servizi Bibliotecario;\t\t\t\t     |\n|3)Visualizza Libreria;\t\t\t\t\t     |\n|4)Stato Prestiti;\t\t\t\t\t     |\n|5)Esci Dal Programma;\t\t\t\t\t     |");
	printf("\n|____________________________________________________________|\n");
	printf("\nQual e' La Tua Risposta:");
	scanf("%d",&a);
	printf("\n");
	return a;
}


int menu_studenti(int d){
	printf("\n======= Benvenuto Nella Sezione Dei Servizi Per Gli Studenti. =======\n");
	printf("=====================================================================\n");
	printf(" __________________________________________\n|Scegli Quale Operazione Utilizzare:\t   |");
	printf("\n|__________________________________________|\n|\t\t\t\t\t   |\n");
	printf("|1)Presta Libro;\t\t\t   |\n|2)Restituisci Libro;\t\t\t   |\n");
	printf("|__________________________________________|\n");
	printf("\nQual e' La Tua Risposta:");
	scanf("%d",&d);
	return d;
}


int menu_bibliotecario(int d){
	printf("\n======= Benvenuto Nella Sezione Dei Servizi Per Il Bibliotecario. =======\n");
	printf("=========================================================================\n");
	printf(" __________________________________________\n|Scegli Quale Operazione Utilizzare:\t   |");
	printf("\n|__________________________________________|\n|\t\t\t\t\t   |\n");
	printf("|1)Aggiungi Libro;\t\t\t   |\n|2)Elimina Libro;\t\t\t   |\n|3)Visualizza Richieste In Sospeso;\t   |\n|4)Esci;\t\t\t\t   |\n");
	printf("|__________________________________________|\n");
	printf("\nQual e' La Tua Risposta:");
	scanf("%d",&d);
	return d;
}

int menu_richieste_sospese(int d){
	printf("\n================= Benvenuto Nella Sezione Delle Richieste. =================\n");
	printf("============================================================================\n");
	printf(" __________________________________________________________________________\n|Scegli Quale Operazione Utilizzare:\t\t\t\t\t   |");
	printf("\n|__________________________________________________________________________|\n|\t\t\t\t\t\t\t\t\t   |\n");
	printf("|1)Richieste Sospese Per Prestiti Effettuati;\t\t\t\t   |\n|2)Richieste Sospese Per Libri Non In Biblioteca;\t\t\t   |\n|3)Esci;\t\t\t\t\t\t\t\t   |\n");
	printf("|__________________________________________________________________________|\n");
	printf("\nQual e' La Tua Risposta:");
	scanf("%d",&d);
	return d;
}
