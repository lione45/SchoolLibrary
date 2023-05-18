#include "libri.h"

bool nodo_vuoto(Libreria *v){
	if(v == NULL){
		return true;
	}else{
		return false;
	}
}

Libreria *costruisci_nodo(char titolo[], char autore[], char isbn[], char stato[]){
	Libreria *rad = (Libreria *)malloc(sizeof(Libreria));
		strcpy(rad->titolo,titolo);
		strcpy(rad->autore,autore);
		strcpy(rad->isbn,isbn);
		strcpy(rad->stato,stato);
		rad->sx = NULL;
		rad->dx = NULL;
	return rad;
}

Libreria *inserisci_libro(Libreria *r, char titolo[], char autore[], char isbn[]){
	char stato[20] = {"Disponibile"};
	if(nodo_vuoto(r)){
		r = costruisci_nodo(titolo,autore, isbn, stato);
		salva_su_file(r);
	}else if(strcoll(titolo,r->titolo) < 0){
		r->sx = inserisci_libro(r->sx, titolo,autore, isbn);
	}else if(strcoll(titolo,r->titolo) > 0){
		r->dx = inserisci_libro(r->dx, titolo,autore, isbn);
	}
	return r;
}

void stampa_libreria(Libreria *pro){
	if(!(nodo_vuoto(pro))){
		stampa_libreria(pro->sx);
		printf("\n===============================================\n");
		printf("\nTitolo: %s;\nAutore: %s;\nISBN: %s;\nStato: %s.\n", pro->titolo, pro->autore, pro->isbn, pro->stato);
		stampa_libreria(pro->dx);
	}
}

void salva_su_file(Libreria *sal){
	FILE *fp = fopen("libreria.txt","a");
	if(fp != NULL){
		if(!(nodo_vuoto(sal))){
			fprintf(fp, "%s,%s,%s,%s;\n", sal->titolo, sal->autore, sal->isbn, sal->stato);
			salva_su_file(sal->sx);
			salva_su_file(sal->dx);
		}
	}else{
		printf("Impossibile Aprire, File Inesistente.\n");
	}
	fclose(fp);
}

Libreria *leggi_da_libreria(Libreria * g){
	FILE *fp = fopen("libreria.txt", "r");
	char titolo[100], autore[100], isbn[20], stato[20], buffer[500];
	char *res, *t, *a, *i, *s;
	if(fp != NULL){
		while(!feof(fp)){
			res = fgets(buffer, 500, fp);
			if(res != NULL){
				t = strtok(res, ",");
				strcpy(titolo,t);
				a = strtok(NULL, ",");
				strcpy(autore,a);
				i = strtok(NULL, ",");
				strcpy(isbn,i);
				s = strtok(NULL, ";");
				strcpy(stato,s);
				g = inserisci_libro_da_file(g, titolo, autore, isbn, stato);
			}
		}
	}
	return g;
	fclose(fp);
}

Libreria *leggi_da_libreria_prestiti(Libreria *h){
	FILE *fd = fopen("storico_prestiti.txt", "r");
	char titolo[100], autore[100], isbn[20], stato[20], buffer[500], nome[30], cognome[30], matr[20];
	char *res, *t, *a, *i, *s, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
				n = strtok(res, ",");
				strcpy(nome,n);
				c = strtok(NULL, ",");
				strcpy(cognome,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ",");
				strcpy(titolo,t);
				a = strtok(NULL, ",");
				strcpy(autore,a);
				i = strtok(NULL, ",");
				strcpy(isbn,i);
				s = strtok(NULL, ";");
				strcpy(stato,s);
				h = inserisci_libro_da_file(h, titolo, autore, isbn, stato);
			}
		}
	}
	return h;
	fclose(fd);
}

Libreria *leggi_da_file(Libreria *j){
	j = leggi_da_libreria_prestiti(j);
	j = leggi_da_libreria(j);
	return j;
}

Libreria *inserisci_libro_da_file(Libreria *r, char titolo[], char autore[], char isbn[], char stato[]){
	if(nodo_vuoto(r)){
		r = costruisci_nodo(titolo,autore, isbn, stato);
	}else if(strcoll(titolo,r->titolo) < 0){
		r->sx = inserisci_libro_da_file(r->sx, titolo, autore, isbn, stato);
	}else if(strcoll(titolo,r->titolo) > 0){
		r->dx = inserisci_libro_da_file(r->dx, titolo, autore, isbn, stato);
	}
	return r;
}

Libreria *dealloca_libreria(Libreria *a){
	if((nodo_vuoto(a))){
		free(a);
	}else{
		dealloca_libreria(a->sx);
		dealloca_libreria(a->dx);
		free(a);
	}
	return a;
}

int ricerca_libro_per_titolo(Libreria *f, Studenti *p, char titolo[], int trovato){
	if(!(nodo_vuoto(f))){
		if(strcmp(titolo,f->titolo) == 0){
			if(strcmp(f->stato,"Prestato") != 0){
				salva_su_file_utenti_libreria(p);
				salva_su_file_libri_prestati(f);
				trovato = 1;
			}else{
				trovato = 2;
			}
		}else if(strcoll(titolo,f->titolo) < 0){
			trovato = ricerca_libro_per_titolo(f->sx, p, titolo, trovato);
		}else if(strcoll(titolo,f->titolo) > 0){
			trovato = ricerca_libro_per_titolo(f->dx, p, titolo, trovato);
		}
	}
	return trovato;
}


int ricerca_libro_per_isbn(Studenti *l, char isbn[], int trovato){
	FILE *fp = fopen("libreria.txt", "r");
	int verifica = 0;
	char titolo[100], autore[100], ISBN[20], stato[20], buffer[500];
	char *res, *t, *a, *i, *s;
	if(fp != NULL){
		while(!feof(fp)){
			res = fgets(buffer, 500, fp);
			if(res != NULL){
				t = strtok(res, ",");
				strcpy(titolo,t);
				a = strtok(NULL, ",");
				strcpy(autore,a);
				i = strtok(NULL, ",");
				strcpy(ISBN,i);
				s = strtok(NULL, ";");
				strcpy(stato,s);
                if(strcmp(ISBN,isbn) == 0){
                        verifica = verifica_se_prestato(titolo,verifica);
                    if(verifica == 0){
                        salva_su_file_utenti_libreria(l);
                        salva_su_file_libri_prestati1(titolo, autore, ISBN);
                        trovato = 1;
                    }else{
                        trovato = 2;
                    }
                }
            }
		}
	}
	fclose(fp);
	return trovato;
}

int verifica_se_prestato(char titolo[],int verifica){
    FILE *fd = fopen("storico_prestiti.txt", "r");
	char tito[100], autore[100], ISBN[20], stato[20], buffer[500], nome[30], cognome[30], matr[20];
	char *res, *t, *a, *i, *s, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
				n = strtok(res, ",");
				strcpy(nome,n);
				c = strtok(NULL, ",");
				strcpy(cognome,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ",");
				strcpy(tito,t);
				a = strtok(NULL, ",");
				strcpy(autore,a);
				i = strtok(NULL, ",");
				strcpy(ISBN,i);
				s = strtok(NULL, ";");
				strcpy(stato,s);
				if (strcmp(tito,titolo) == 0){
					verifica =1;
				}
			}
		}
	}
	fclose(fd);
	return verifica;
}


char pulisci_buff(char p[]){
	int n_dim;
	if (strrchr(p,'\n')){
		n_dim = strlen(p)-1;
		p[n_dim]='\0';
	}
	return *p;
}


void salva_su_file_libri_prestati(Libreria *sal){
	FILE *fp = fopen("storico_prestiti.txt","a");
	if(fp != NULL){
		if(!(nodo_vuoto(sal))){
			fprintf(fp, "%s,%s,%s,Prestato;\n", sal->titolo, sal->autore, sal->isbn);
		}
	}
	fclose(fp);
}

void salva_su_file_libri_prestati1(char titolo[], char autore[], char isbn[]){
	FILE *fp = fopen("storico_prestiti.txt","a");
	if(fp != NULL){
			fprintf(fp, "%s,%s,%s,Prestato;\n",titolo, autore, isbn);
	}
	fclose(fp);
}

void salva_su_file_libri_prestiti_sospesi(char titolo[]){
	FILE *fp = fopen("prestiti_sospesi.txt","a");
	if(fp != NULL){
			fprintf(fp, "%s;\n", titolo);
	}
	fclose(fp);
}

void salva_su_file_libri_inesistenti(char titolo[]){
	FILE *fp = fopen("prestiti_sospesi_non_presenti.txt","a");
	if(fp != NULL){
			fprintf(fp, "%s;\n", titolo);
	}
	fclose(fp);
}


char estrai_isbn(Libreria *es, char titolo[], char isbn[]){
	if(!(nodo_vuoto(es))){
		if(strcmp(titolo,es->titolo) == 0){
			strcpy(isbn,es->isbn);
		}else if(strcoll(titolo,es->titolo) < 0){
			*isbn = estrai_isbn(es->sx, titolo, isbn);
		}else if(strcoll(titolo,es->titolo) > 0){
			*isbn = estrai_isbn(es->dx, titolo, isbn);
		}
	}
	return *isbn;
}

char estrai_autore(Libreria *es, char titolo[], char autore[]){
	if(!(nodo_vuoto(es))){
		if(strcmp(titolo,es->titolo) == 0){
			strcpy(autore,es->autore);
		}else if(strcoll(titolo,es->titolo) < 0){
			*autore = estrai_autore(es->sx, titolo, autore);
		}else if(strcoll(titolo,es->titolo) > 0){
			*autore = estrai_autore(es->dx, titolo, autore);
		}
	}
	return *autore;
}

int elimina_da_biblioteca(char titolo[], char isbn[], int eliminato){
    Libreria *f = NULL;
    FILE *fp = fopen("libreria.txt","r");
    int verifica = 0;
	char  tito[100], autore[100], ISBN[40], stato[50], buffer[900];
	char *res, *t, *a, *i, *s;
	if(fp != NULL){
		while(!feof(fp)){
			res = fgets(buffer, 900, fp);
			if(res != NULL){
				t = strtok(res, ",");
				strcpy(tito,t);
				a = strtok(NULL, ",");
				strcpy(autore,a);
				i = strtok(NULL, ",");
				strcpy(ISBN,i);
				s = strtok(NULL, ";");
				strcpy(stato,s);
				if(strcmp(isbn,ISBN) != 0 || strcmp(tito,titolo) != 0){
                        f = inserisci_libro_per_elimina(f,tito,autore,ISBN);
				}else{
				    verifica = verifica_elimina(titolo,isbn, verifica);
                    if(verifica == 0){
                        eliminato = 1;
                    }else{
                        f = inserisci_libro_per_elimina(f,tito,autore,isbn);
                        eliminato = 2;
                    }
                }
            }
        }
	}
	fclose(fp);
	salva_per_elimina(f);
	f=dealloca_libreria(f);
	return eliminato;
}

void salva(FILE *nm, Libreria *al){
		if(!(nodo_vuoto(al))){
			fprintf(nm, "%s,%s,%s,%s;\n", al->titolo, al->autore, al->isbn, al->stato);
			salva(nm,al->sx);
			salva(nm, al->dx);
		}

}

void salva_per_elimina(Libreria *sal){
	FILE *fp = fopen("libreria.txt","w");
	fclose(fp);
	FILE *gh = fopen("libreria.txt","w");
	if(gh != NULL){
        salva(gh, sal);
	}else{
		printf("Impossibile Aprire, File Inesistente.\n");
	}
	fclose(fp);
}

int verifica_elimina(char titolo[],char isbn[], int verifica){
    FILE *fd = fopen("storico_prestiti.txt", "r");
	char tito[100], autore[100], ISBN[40], stato[30], buffer[900], nome[30], cognome[30], matr[20];
	char *res, *t, *a, *i, *s, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 900, fd);
			 *buffer = pulisci_buff(buffer);
			if(res != NULL){
				n = strtok(res, ",");
				strcpy(nome,n);
				c = strtok(NULL, ",");
				strcpy(cognome,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ",");
				strcpy(tito,t);
				a = strtok(NULL, ",");
				strcpy(autore,a);
				i = strtok(NULL, ",");
				strcpy(ISBN,i);
				s = strtok(NULL, ";");
				strcpy(stato,s);
				if (strcmp(ISBN,isbn) == 0 && strcmp(tito,titolo) == 0){
					verifica = 1;
				}
			}
		}
	}
	fclose(fd);
	return verifica;

}

Libreria *inserisci_libro_per_elimina(Libreria *r, char titolo[], char autore[], char isbn[]){
	char stato[30] = {"Disponibile"};
	if(nodo_vuoto(r)){
		r = costruisci_nodo(titolo,autore, isbn, stato);
	}else if(strcoll(titolo,r->titolo) < 0){
		r->sx = inserisci_libro_per_elimina(r->sx, titolo,autore, isbn);
	}else if(strcoll(titolo,r->titolo) > 0){
		r->dx = inserisci_libro_per_elimina(r->dx, titolo,autore, isbn);
	}
	return r;
}
