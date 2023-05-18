#include "richieste.h"

int inizializza_richiesta(int a[], int dim){
	if(dim < MAX){
		a[0] = 0;
		a[dim + 1] = 1;
	}
	return *a;
}

bool richieste_piene(int a[], int dim){
		return a[0] == a[dim + 1];
}

bool richieste_vuote(int b[]){
		return b[0] == 0;
}

void inserisci_richiesta(int c[], int dim, int val){
	if(!(richieste_piene(c, dim))){
		c[c[dim + 1]] = val;
		if(richieste_vuote(c)){
			c[0] = 1;
		}
		c[dim + 1] = (c[dim + 1] % (dim)) + 1;
	}else{
		printf("La Coda è Piena.\n");
	}
}

int togli_richiesta(int e[], int dim){
	int val;
	if(!(richieste_vuote(e))){
		val = e[e[0]];
		e[0]=(e[0]%(dim))+1;
		if(richieste_piene(e,dim)){
			*e = inizializza_richiesta(e, dim);
		}
	}
	return val;
}

void stampa(int s[], int dim){
    int val;
    if(!(richieste_vuote(s))){
        val = togli_richiesta(s, dim);
        printf("%d-> ", val);
        stampa(s, dim);
        inserisci_richiesta(s, dim, val);
    }
}

void reverse(int r[], int dim){
    int val;
    if(!(richieste_vuote(r))){
        val = togli_richiesta(r, dim);
        reverse(r, dim);
        inserisci_richiesta(r, dim, val);
    }
}

void stampa_richiesta(int p[], int dim){
    stampa(p, dim);
    reverse(p, dim);
}

