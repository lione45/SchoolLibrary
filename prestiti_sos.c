#include "prestiti_sos.h"


Prestiti_sos *alloca_prestito_sos(char no[], char co[], char ma[], char ti[]){
    Prestiti_sos *p = (Prestiti_sos *)malloc(sizeof(Prestiti_sos));
    strcpy(p->nome,no);
    strcpy(p->cognome,co);
    strcpy(p->matr,ma);
    strcpy(p->titolo,ti);
    p->next = NULL;
    return p;
}

Prestiti_sos *inseririsci_prestito_sos(Prestiti_sos *k, char no[], char co[], char ma[], char ti[]){
    if(k == NULL){
        k = alloca_prestito_sos(no,co,ma,ti);
    }else{
        k->next = inseririsci_prestito_sos(k->next,no,co,ma,ti);
    }
    return k;
}

Prestiti_sos *dealloca_prestito_sos(Prestiti_sos *d){
    if(d!= NULL){
            dealloca_prestito_sos(d->next);
            d->next = NULL;
            free(d);
    }
    return d;
}

void salva_su_file_lista_prestiti_sos(Prestiti_sos* l){
	FILE *fp = fopen("prestiti_sospesi.txt","w");
	if(fp != NULL){
		while(l != NULL){
			fprintf(fp, "%s,%s,%s,%s;\n", l->nome, l->cognome, l->matr, l->titolo);
			l=l->next;
		}
	}
	fclose(fp);
}

void rimuovi_da_prestiti_sos(char matricola[], char titolo []){
    Prestiti_sos *f = NULL;
    FILE *fp = fopen("prestiti_sospesi.txt","r");
	char  tito[100], buffer[500], nome[30], cognome[30], matr[20];
	char *res, *t, *n, *c, *m;
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
				t = strtok(NULL, ";");
				strcpy(tito,t);
				if(strcmp(matr,matricola) != 0 || strcmp(tito,titolo) != 0){
                    f = inseririsci_prestito_sos(f,nome,cognome,matr,tito);
                }
            }
        }

	}
	fclose(fp);
	salva_su_file_lista_prestiti_sos(f);
	f=dealloca_prestito_sos(f);
}


void salva_su_file_lista_libri_inesistenti(Prestiti_sos* l){
	FILE *fp = fopen("prestiti_sospesi_non_presenti.txt","w");
	if(fp != NULL){
		while(l != NULL){
			fprintf(fp, "%s,%s,%s,%s;\n", l->nome, l->cognome, l->matr, l->titolo);
			l=l->next;
		}
	}
	fclose(fp);
}

void rimuovi_da_libri_inesistenti(char matricola[], char titolo [], char isbn[]){
    Prestiti_sos *f = NULL;
    FILE *fp = fopen("prestiti_sospesi_non_presenti.txt","r");
	char  tito[100], buffer[500], nome[30], cognome[30], matr[20];
	char *res, *t, *n, *c, *m;
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
				t = strtok(NULL, ";");
				strcpy(tito,t);
				if(strcmp(matr,matricola) != 0 && (strcmp(tito,titolo) != 0 || strcmp(tito,isbn) != 0)){
                    f = inseririsci_prestito_sos(f,nome,cognome,matr,tito);
                }
            }
        }

	}
	fclose(fp);
	salva_su_file_lista_libri_inesistenti(f);
	f=dealloca_prestito_sos(f);
}
