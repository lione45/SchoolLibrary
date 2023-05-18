#include "prestiti.h"


Prestiti *alloca_prestito(char no[], char co[], char ma[], char ti[], char au[], char is[], char st[]){
    Prestiti *p = (Prestiti *)malloc(sizeof(Prestiti));
    strcpy(p->nome,no);
    strcpy(p->cognome,co);
    strcpy(p->matr,ma);
    strcpy(p->titolo,ti);
    strcpy(p->autore,au);
    strcpy(p->isbn,is);
    strcpy(p->stato,st);
    p->next = NULL;
    return p;
}

Prestiti *inseririsci_prestito(Prestiti* s, char no[], char co[], char ma[], char ti[], char au[], char is[], char st[]){
    if(s == NULL){
        s = alloca_prestito(no,co,ma,ti,au,is,st);
    }else{
        s->next = inseririsci_prestito(s->next,no,co,ma,ti,au,is,st);
    }
    return s;
}

Prestiti *dealloca_prestito(Prestiti *d){
    if(d!= NULL){
            dealloca_prestito(d->next);
            d->next = NULL;
            free(d);
    }
    return d;
}

void salva_su_file_lista_prestiti(Prestiti * l){
	FILE *fp = fopen("storico_prestiti.txt","w");
	if(fp != NULL){
		while(l != NULL){
			fprintf(fp, "%s,%s,%s,%s,%s,%s,%s;\n", l->nome, l->cognome, l->matr, l->titolo, l->autore, l->isbn, l->stato);
			l=l->next;
		}
	}
	fclose(fp);
}

int restituisci(char matricola[], char titolo [], int restituito){
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
				if(strcmp(matr,matricola) != 0 || strcmp(tito,titolo) != 0){
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
