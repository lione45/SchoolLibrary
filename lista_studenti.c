#include "lista_studenti.h"

Studenti *nuovo_nodo(char nome[], char cognome[], char matr[]){
	Studenti *no = (Studenti *)malloc(sizeof(Studenti));
	strcpy(no->nome,nome);
	strcpy(no->cognome,cognome);
	strcpy(no->matricola,matr);
	no->next = NULL;
	return no;
}

Studenti *inserisci_studenti_in_coda(Studenti *c){
	char nome[50], cognome[50], matr[20];
	if(c == NULL){
		printf("Inserire Il Nome Dello Studente:");
		fgets(nome, 50 , stdin);
		*nome = pulisci(nome);
		printf("Inserire Il Cognome Dello Studente:");
		fgets(cognome, 50 , stdin);
		*cognome = pulisci(cognome);
		printf("Inserire La Matricola Dello Studente:");
		fgets(matr, 20 , stdin);
		*matr = pulisci(matr);
		c = nuovo_nodo(nome, cognome, matr);
	}else{
		c->next = inserisci_studenti_in_coda(c->next);
	}
	return c;
}

Studenti *crea_lista_studenti(Studenti *m){
	int i = 0, dim_s;
	printf("Dimensione Lista Studenti:");
	scanf("%d", &dim_s);
	while('\n'!=getchar());
	while(i < dim_s){
		m = inserisci_studenti_in_coda(m);
		i++;
	}
	return m;
}

void stampa_lista_studenti(Studenti *s){
	if(s != NULL){
		printf("Nome: %s;\nCognome: %s;\nMatricola: %s.", s->nome, s->cognome, s->matricola);
        printf("\n============================\n");
    }
}


Studenti *dealloca_lista_studenti(Studenti *d){
	if(d != NULL){
		dealloca_lista_studenti(d->next);
		d->next = NULL;
		free(d);
	}
	return d;
}

char pulisci(char p[]){
	int n_dim;
	if (strrchr(p,'\n')){
		n_dim = strlen(p)-1;
		p[n_dim]='\0';
	}
	return *p;
}

void salva_su_file_utenti_libreria(Studenti * l){
	FILE *fp = fopen("storico_prestiti.txt","a");
	if(fp != NULL){
		if(l != NULL){
			fprintf(fp, "%s,%s,%s,", l->nome, l->cognome, l->matricola);
		}
	}
	fclose(fp);
}

void salva_su_file_utenti_prestiti_sospesi(Studenti * l){
	FILE *fp = fopen("prestiti_sospesi.txt","a");
	if(fp != NULL){
		if(l != NULL){
			fprintf(fp, "%s,%s,%s,", l->nome, l->cognome, l->matricola);
		}
	}
	fclose(fp);
}

void salva_su_file_utenti_prestiti_inesistenti(Studenti * l){
	FILE *fp = fopen("prestiti_sospesi_non_presenti.txt","a");
	if(fp != NULL){
		if(l != NULL){
			fprintf(fp, "%s,%s,%s,", l->nome, l->cognome, l->matricola);
		}
	}
	fclose(fp);
}

int verifica_max_prestiti(Studenti *h, int count){
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
				if (strcmp(h->nome,n) == 0 && strcmp(h->cognome,c) == 0 && strcmp(h->matricola,m) == 0){
					count++;
				}
			}
		}
	}
	fclose(fd);
	return count;

}

int stato_prestiti(int n_prestiti){
	FILE *fd = fopen("storico_prestiti.txt", "r");
	char titolo[100], autore[100], isbn[20], stato[20], buffer[500], nome[30], cognome[30], matr[20];
	char *res, *t, *a, *i, *s, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
                n_prestiti++;
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
			}
		}
	fclose(fd);
	}
    return n_prestiti;
}

int stato_sospesi(int count){
	FILE *fd = fopen("prestiti_sospesi.txt", "r");
	char titolo[100], buffer[500], nome[30], cognome[30], matr[20];
	char *res, *t, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
                count++;
				n = strtok(res, ",");
				strcpy(nome,n);
				c = strtok(NULL, ",");
				strcpy(cognome,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ";");
				strcpy(titolo,t);
                printf("================================================================");
				printf("\nNome: %s;\nCognome: %s;\nMatricola: %s.\nTitolo: %s.\n\n",nome, cognome, matr, titolo);
			}
		}
    }
    fclose(fd);
    return count;
}

int stato_non_presenti(int Count){
	FILE *fd = fopen("prestiti_sospesi_non_presenti.txt", "r");
	char titolo[100], buffer[500], nome[30], cognome[30], matr[20];
	char *res, *t, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
                Count++;
				n = strtok(res, ",");
				strcpy(nome,n);
				c = strtok(NULL, ",");
				strcpy(cognome,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ";");
				strcpy(titolo,t);
                printf("================================================================");
				printf("\nNome: %s;\nCognome: %s;\nMatricola: %s.\nTitolo O ISBN: %s.\n\n",nome, cognome, matr, titolo);
			}
		}
    }
    fclose(fd);
    return Count;
}

int verifica_richieste_prestiti(char titolo[], int count){
	FILE *fd = fopen("prestiti_sospesi.txt", "r");
	char tito[100], buffer[500], nome[30], cognome[30], matr[20];
	char *res, *t, *n, *c, *m;
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
				t = strtok(NULL, ";");
				strcpy(tito,t);
				if (strcmp(tito,titolo) == 0){
					count++;
				}
			}
		}
	}
	fclose(fd);
	return count;

}

int verifica_richieste_aggiunta_libro(char titolo[], char isbn[], int count){
	FILE *fd = fopen("prestiti_sospesi_non_presenti.txt", "r");
	char tito[100], buffer[500], nome[30], cognome[30], matr[20];
	char *res, *t, *n, *c, *m;
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
				t = strtok(NULL, ";");
				strcpy(tito,t);
				if (strcmp(tito,titolo) == 0 || strcmp(tito,isbn) == 0){
					count++;
				}
			}
		}
	}
	fclose(fd);
	return count;

}

int verifica_Max_prestiti(char matricola[], int count){
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
				if (strcmp(matricola,matr) == 0){
					count++;
				}
			}
		}
	}
	fclose(fd);
	return count;

}

void salva_prestito(char nome[], char cognome[] ,char matricola[], char titolo[], char autore[], char isbn[]){
    FILE *fp = fopen("storico_prestiti.txt","a");
	if(fp != NULL){
			fprintf(fp, "%s,%s,%s,%s,%s,%s,Prestato;\n", nome,cognome,matricola,titolo,autore,isbn);
		}
	fclose(fp);
}

char estrai_nome(char matricola[], char nome[]){
   	FILE *fd = fopen("prestiti_sospesi.txt", "r");
	char tito[100], buffer[500], no[30], cognome[30], matr[20];
	char *res, *t, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
				n = strtok(res, ",");
				strcpy(no,n);
				c = strtok(NULL, ",");
				strcpy(cognome,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ";");
				strcpy(tito,t);
				if (strcmp(matr,matricola) == 0){
					strcpy(nome,no);
				}
			}
		}
	}
	fclose(fd);
	return *nome;

}

char estrai_cognome(char matricola[], char cognome[]){
    	FILE *fd = fopen("prestiti_sospesi.txt", "r");
	char tito[100], buffer[500], nome[30], co[30], matr[20];
	char *res, *t, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
				n = strtok(res, ",");
				strcpy(nome,n);
				c = strtok(NULL, ",");
				strcpy(co,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ";");
				strcpy(tito,t);
				if (strcmp(matr,matricola) == 0){
					strcpy(cognome,co);
				}
			}
		}
	}
	fclose(fd);
	return *cognome;

}

char estrai_matricola(char titolo[], char matricola[]){
    FILE *fd = fopen("prestiti_sospesi.txt", "r");
	char tito[100], buffer[500], nome[30], co[30], matr[20];
	char *res, *t, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
				n = strtok(res, ",");
				strcpy(nome,n);
				c = strtok(NULL, ",");
				strcpy(co,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ";");
				strcpy(tito,t);
				if (strcmp(tito,titolo) == 0){
					strcpy(matricola,matr);
				}
			}
		}
	}
	fclose(fd);
	return *matricola;

}

char estrai_nome_da_aggiunta(char matricola[], char nome[]){
   	FILE *fd = fopen("prestiti_sospesi_non_presenti.txt", "r");
	char tito[100], buffer[500], no[30], cognome[30], matr[20];
	char *res, *t, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
				n = strtok(res, ",");
				strcpy(no,n);
				c = strtok(NULL, ",");
				strcpy(cognome,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ";");
				strcpy(tito,t);
				if (strcmp(matr,matricola) == 0){
					strcpy(nome,no);
				}
			}
		}
	}
	fclose(fd);
	return *nome;

}

char estrai_cognome_da_aggiunta(char matricola[], char cognome[]){
    	FILE *fd = fopen("prestiti_sospesi_non_presenti.txt", "r");
	char tito[100], buffer[500], nome[30], co[30], matr[20];
	char *res, *t, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
				n = strtok(res, ",");
				strcpy(nome,n);
				c = strtok(NULL, ",");
				strcpy(co,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ";");
				strcpy(tito,t);
				if (strcmp(matr,matricola) == 0){
					strcpy(cognome,co);
				}
			}
		}
	}
	fclose(fd);
	return *cognome;

}

char estrai_matricola_da_aggiunta(char titolo[], char isbn[], char matricola[]){
    FILE *fd = fopen("prestiti_sospesi_non_presenti.txt", "r");
	char tito[100], buffer[500], nome[30], co[30], matr[20];
	char *res, *t, *n, *c, *m;
	if(fd != NULL){
		while(!feof(fd)){
			res = fgets(buffer, 500, fd);
			if(res != NULL){
				n = strtok(res, ",");
				strcpy(nome,n);
				c = strtok(NULL, ",");
				strcpy(co,c);
				m = strtok(NULL, ",");
				strcpy(matr,m);
				t = strtok(NULL, ";");
				strcpy(tito,t);
				if (strcmp(tito,titolo) == 0 || strcmp(tito,isbn) == 0){
					strcpy(matricola,matr);
				}
			}
		}
	}
	fclose(fd);
	return *matricola;

}

int restituisci_corrente(Studenti *doh, char titolo [], int restituito){
    Prestiti *f = NULL;
    FILE *fp = fopen("storico_prestiti.txt","r");
	char  tito[100], autore[100], isbn[20], stato[20], buffer[500], nome[30], cognome[30], matr[20];
	char *res, *t, *a, *i, *s, *n, *c, *m;
	if(fp != NULL){
		while(!feof(fp)){
			res = fgets(buffer, 500, fp);
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
				strcpy(isbn,i);
				s = strtok(NULL, ";");
				strcpy(stato,s);
				if(strcmp(matr,doh->matricola) != 0 || strcmp(tito,titolo) != 0){
                    f = inseririsci_prestito(f,nome,cognome,matr,tito,autore,isbn,stato);
				}else{
                    restituito -= 1;
				}
			}
		}

	}
	fclose(fp);
	salva_su_file_lista_prestiti(f);
	f=dealloca_prestito(f);
	return restituito;
}

void stampa_prestiti_utente_corrente(Studenti *so){
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
				if(strcmp(so->matricola,matr) == 0){
                    printf("==============================");
                    printf("\nNome: %s;\nCognome: %s;\nMatricola: %s;\nTitolo: %s;\nAutore: %s\nISBN: %s\nStato: %s.\n\n",nome, cognome, matr, titolo, autore, isbn, stato);
				}
			}
		}
	fclose(fd);
	}
}

void stampa_prestiti_altri_utenti(Studenti *st){
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
				if(strcmp(st->matricola,matr) != 0){
                    printf("==============================");
                    printf("\nNome: %s;\nCognome: %s;\nMatricola: %s;\nTitolo: %s;\nAutore: %s\nISBN: %s\nStato: %s.\n\n",nome, cognome, matr, titolo, autore, isbn, stato);
				}
			}
		}
	fclose(fd);
	}
}

void stampa_prestiti(){
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
                printf("==============================");
                printf("\nNome: %s;\nCognome: %s;\nMatricola: %s;\nTitolo: %s;\nAutore: %s\nISBN: %s\nStato: %s.\n\n",nome, cognome, matr, titolo, autore, isbn, stato);
			}
		}
	fclose(fd);
	}
}
