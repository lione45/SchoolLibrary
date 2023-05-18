#include "libri.h"
#include "richieste.h"
#include "menu.h"

int main(){
	char loop = 'n';
	Studenti *L1 = NULL;
	Libreria *L2 = NULL;
	L2 = leggi_da_file(L2);
	int i = 0, dimensione, j = 1, elimina = 0;
	int scelta_ini, scelta2, esito = 0, scelta_menu, n_richiesta, dim, max_prestiti = 0, v_r, n_prestiti = 0, n_restituiti = 0;
	int scelta1[MAX], n_prestiti1 = 0, n_richieste_sospese = 0, n_richieste_libri_inesistenti = 0, n_studenti = 0;
	char ricerca[100], scelta3[10], titolo[100], isbn[30], salva, corrente;
	char titolo1[100], matricola[30], nome[50], cognome[50], autore[100], matricola1[30];
	while(loop == 'n'){
		do{
			scelta_ini = menu_iniziale(scelta_ini);
			while('\n'!=getchar());
			switch(scelta_ini){
				case 1:
					L1 = crea_lista_studenti(L1);
					while(L1 != NULL){
                        Libreria *L2 = NULL;
                        L2 = leggi_da_file(L2);
                        printf("\n\n============================");
                        printf("\nUtente Corrente:\n");
                        printf("============================\n");
                        stampa_lista_studenti(L1);
						printf("\n\nQuante Richieste Vuole Effettuare Lo Studente?\nSi Possono Effettuare: Minimo 1 Richiesta, Massimo 3 Richieste.\n");
						printf("Qual e' La Tua Risposta:");
						scanf("%d",&dim);
						*scelta1 = inizializza_richiesta(scelta1, dim);
						if(dim > 0 && dim <= 3){
                            printf("\n\n============================");
                            printf("\nUtente Corrente:\n");
                            printf("============================\n");
                            stampa_lista_studenti(L1);
							while('\n'!=getchar());
							while(!(richieste_piene(scelta1,dim))){
								scelta_menu = menu_studenti(scelta_menu);
								if(scelta_menu == 1 || scelta_menu == 2){
                                    inserisci_richiesta(scelta1,dim,scelta_menu);
                                    printf("\n================================================");
                                    printf("\nRichiesta Inserita Correttamente Nella Coda Delle Richieste.\n");
                                    printf("================================================\n\n");
								}else{
                                    printf("\n==============================");
                                    printf("\nScelta Errata, Ritenta.");
                                    printf("\n==============================\n\n");
                                }
                            }
							while('\n'!=getchar());
							do{
                            max_prestiti = 0;
							max_prestiti = verifica_max_prestiti(L1, max_prestiti);
							n_richiesta = togli_richiesta(scelta1,dim);
                            if(max_prestiti < 3 || n_richiesta == 2){
                                switch(n_richiesta){
								case 1:
								    printf("\n============================");
                                    printf("\nOperazione Di Prestito\n");
                                    printf("\n============================");
                                    printf("\nUtente Corrente:\n");
                                    printf("============================\n");
                                    stampa_lista_studenti(L1);
									printf("\nVuoi Cercare Il Libro Per ISBN O Per Titolo?");
									printf("\nQual e' La Tua Risposta:");
									fgets(scelta3, 10, stdin);
									*scelta3 = pulisci_buff(scelta3);
									if(strcmp(scelta3,"Titolo") == 0 || strcmp(scelta3,"titolo") == 0){
                                        esito = 0;
										printf("\nInserisci Titolo Da Cercare:");
										fgets(ricerca, 100, stdin);
										*ricerca = pulisci_buff(ricerca);
										esito = ricerca_libro_per_titolo(L2, L1, ricerca, esito);
										if(esito == 0){
											printf("\nSpiacente Ma Il  Libro Cercato Non e' Presente Nella Libreria Oppure Il Titolo Inserito Non e' Corretto.\n");
											printf("Vuoi Salvare La Richiesta Per Un Secondo Momento?\n\n\tY)Per Salvare;\n\tN)Per Proseguire;\n\nLa Tua Risposta:");
											scanf("\n%c", &salva);
											while('\n'!=getchar());
											if(salva == 'y' || salva == 'Y'){
                                                   salva_su_file_utenti_prestiti_inesistenti(L1);
                                                   salva_su_file_libri_inesistenti(ricerca);
                                                    printf("\n\n==============================");
                                                    printf("\nRichiesta Libro Salvata Nelle Lista Di Possibili Libri In Aggiunta Alla Lbreria.");
                                                    printf("\n==============================\n\n");
											}
										}else if(esito == 1){
                                                    printf("\n==============================");
                                                    printf("\nIl Libro: %s e' Presente Nella Libreria.\nPrestito Eseguito Con Successo.", ricerca);
                                                    printf("\n==============================\n\n");
										}else if(esito == 2){
											printf("\nIl Libro: %s e' Presente Nella Libreria Ma e' Stato Gia' Prestato.\n", ricerca);
                                            printf("Vuoi Salvare La Richiesta Per Un Secondo Momento?\n\n\tY)Per Salvare;\n\tN)Per Proseguire;\n\nLa Tua Risposta:");
                                            scanf("\n%c", &salva);
											while('\n'!=getchar());
											if(salva == 'y' || salva == 'Y'){
                                                    salva_su_file_utenti_prestiti_sospesi(L1);
                                                    salva_su_file_libri_prestiti_sospesi(ricerca);
                                                    printf("\n\n==============================");
                                                    printf("\nRichiesta Libro Salvata Nelle Richieste In Sospeso.");
                                                    printf("\n==============================\n\n");
											}
										}
									}else if(strcmp(scelta3,"ISBN") == 0 || strcmp(scelta3,"isbn") == 0){
										esito = 0;
                                        printf("Inserisci ISBN Da Cercare:");
										fgets(ricerca, 100, stdin);
										*ricerca = pulisci_buff(ricerca);
										esito = ricerca_libro_per_isbn(L1, ricerca, esito);
										if(esito == 0){
											printf("\nSpiacente Ma Il  Libro Cercato Non e' Presente Nella Libreria Oppure L'ISBN Inserito Non e' Corretto.\n");
                                            printf("Vuoi Salvare La Richiesta Per Un Secondo Momento?\n\n\tY)Per Salvare;\n\tN)Per Proseguire;\n\nLa Tua Risposta:");
											scanf("\n%c", &salva);
											while('\n'!=getchar());
											if(salva == 'y' || salva == 'Y'){
												salva_su_file_utenti_prestiti_inesistenti(L1);
                                                salva_su_file_libri_inesistenti(ricerca);
                                                printf("\n\n==============================");
                                                printf("\nRichiesta Libro Salvata Nelle Lista Di Possibili Libri In Aggiunta Alla Lbreria.");
                                                printf("\n==============================\n\n");
											}
										}else if(esito == 1){
                                             printf("\n==============================");
                                             printf("\nIl Libro Associato A Questo ISBN: %s e' Presente Nella Libreria.\nIl Prestito e' Stato Eseguito Con Successo.", ricerca);
                                             printf("\n==============================\n\n");
										}else if(esito == 2){
											printf("\nIl Libro Associato A Questo ISBN: %s e' Presente Nella Libreria Ma e' Stato Gia' Prestato.\n",ricerca);
                                            printf("Vuoi Salvare La Richiesta Per Un Secondo Momento?\n\n\tY)Per Salvare;\n\tN)Per Proseguire;\n\nLa Tua Risposta:");
											scanf("\n%c", &salva);
											while('\n'!=getchar());
											if(salva == 'y' || salva == 'Y'){
                                                    salva_su_file_utenti_prestiti_sospesi(L1);
                                                    salva_su_file_libri_prestiti_sospesi(ricerca);
                                                    printf("\n\n==============================");
                                                    printf("\nRichiesta Libro Salvata Nelle Richieste In Sospeso.");
                                                    printf("\n==============================\n\n");
											}
										}
									}
									break;
								while('\n'!=getchar());
								case 2:
                                    printf("\n==============================");
                                    printf("\nOperazione Di Restituzione\n");
                                    printf("==============================\n\n");
                                    n_prestiti = 0;
                                    n_prestiti = stato_prestiti(n_prestiti);
                                    max_prestiti = 0;
                                    max_prestiti = verifica_max_prestiti(L1, max_prestiti);
                                    if(n_prestiti != 0){
                                        printf("Vuoi Effettuare L'Operazione Di Restituzione Per L'utente Corrente O Per Un Altro Utente?\n\nY)Restituzione Per L'utente Corrente;\nN)Restituzione Per Un Altro Utente;\n");
                                        printf("\n\nLa Tua Risposta:");
                                        scanf("\n%c", &corrente);
                                        while('\n'!=getchar());
                                        if(max_prestiti != 0 && (corrente == 'Y' || corrente == 'y')){
                                            stampa_prestiti_utente_corrente(L1);
                                            printf("Inserisci Il Titolo Del Libro Da Restituire:");
                                            fgets(titolo1, 100, stdin);
                                            *titolo1 = pulisci_buff(titolo1);
                                            n_restituiti = restituisci_corrente(L1, titolo1, n_prestiti);
                                            if(n_restituiti != n_prestiti){
                                                printf("\n==============================");
                                                printf("\nRestituzione Avvenuta Con Successo.");
                                                printf("\n==============================\n\n");
                                                n_richieste_sospese = 0;
                                                max_prestiti = 0;
                                                *isbn = estrai_isbn(L2, titolo1, isbn);
                                                n_richieste_sospese = verifica_richieste_prestiti(isbn, n_richieste_sospese);
                                                if(n_richieste_sospese > 0){
                                                    n_studenti = n_richieste_sospese;
                                                    do{
                                                         *matricola1 = estrai_matricola(isbn,matricola1);
                                                         max_prestiti = verifica_Max_prestiti(matricola1, max_prestiti);
                                                         *nome = estrai_nome(matricola1,nome);
                                                         *cognome = estrai_cognome(matricola1, cognome);
                                                         printf("Attenzione Lo Studente: %s %s Aveva Richiesto Il Libro %s.\nEffettuare La Richiesta Di Prestito A Suo Nome?", nome, cognome,titolo1);
                                                         printf("\n\nY)Per Confermare;\nN)Per Rifiutare.\n\nLa Tua Risposta:");
                                                         scanf("\n%c", &salva);
                                                         while('\n'!=getchar());
                                                         if(max_prestiti < 3 && (salva == 'y' || salva == 'Y')){
                                                                *isbn = estrai_isbn(L2, titolo1, isbn);
                                                                *autore = estrai_autore(L2, titolo1, autore);
                                                                salva_prestito(nome,cognome,matricola1,titolo1,autore,isbn);
                                                                rimuovi_da_prestiti_sos(matricola1, isbn);
                                                                printf("\n==============================");
                                                                printf("\nPrestito Eseguito Con Successo.");
                                                                printf("\n==============================\n\n");
                                                                n_studenti = 0;
                                                        }else if(max_prestiti == 3 && (salva == 'y' || salva == 'Y')){
                                                                printf("\n==============================");
                                                                printf("\nAttenzione Lo Studente Ha Terminato I Prestiti Possibili.\n Retituire Uno Dei Libri Prima Di Effettuare Un Nuovo Prestito.");
                                                                printf("\n==============================\n\n");
                                                                rimuovi_da_prestiti_sos(matricola1, titolo1);
                                                                n_studenti -= 1;
                                                        }else if(salva == 'n' || salva == 'N'){
                                                                rimuovi_da_prestiti_sos(matricola1, titolo1);
                                                                n_studenti -= 1;
                                                        }
                                                    }while(n_studenti != 0);
                                                }
                                            }else if(n_restituiti == n_prestiti){
                                                printf("\n==============================");
                                                printf("\nAttenzione Restituzione Fallita Matricola Studente O Titolo Libro Inseriti Errati.");
                                                printf("\n==============================\n\n");
                                            }
                                        }else if(max_prestiti == 0 && (corrente == 'Y' || corrente == 'y')){
                                            printf("\n==============================");
                                            printf("\nNon Esistono Prestiti Per Lo Studente Corrente Al Momento.");
                                            printf("\n==============================\n\n");
                                        }else if(corrente == 'n' || corrente == 'N'){
                                            stampa_prestiti_altri_utenti(L1);
                                            printf("\nInserisci La Matricola Dello Studente Che Deve Restituire Il Libro:");
                                            fgets(matricola, 100, stdin);
                                            *matricola = pulisci_buff(matricola);
                                            printf("Inserisci Il Titolo Del Libro Da Restituire:");
                                            fgets(titolo1, 100, stdin);
                                            *titolo1 = pulisci_buff(titolo1);
                                            n_restituiti = restituisci(matricola, titolo1, n_prestiti);
                                            if(n_restituiti != n_prestiti){
                                                printf("\n==============================");
                                                printf("\nRestituzione Avvenuta Con Successo.");
                                                printf("\n==============================\n\n");
                                                n_richieste_sospese = 0;
                                                max_prestiti = 0;
                                                *isbn = estrai_isbn(L2, titolo1, isbn);
                                                n_richieste_sospese = verifica_richieste_prestiti(titolo1, n_richieste_sospese);
                                                if(n_richieste_sospese > 0){
                                                    n_studenti = n_richieste_sospese;
                                                    do{
                                                         *matricola1 = estrai_matricola(isbn,matricola1);
                                                         max_prestiti = verifica_Max_prestiti(matricola1, max_prestiti);
                                                         *nome = estrai_nome(matricola1,nome);
                                                         *cognome = estrai_cognome(matricola1, cognome);
                                                         printf("Attenzione Lo Studente: %s %s Aveva Richiesto Il Libro %s.\nEffettuare La Richiesta Di Prestito A Suo Nome?", nome, cognome,titolo1);
                                                         printf("\nY)Per Confermare;\nN)Per Rifiutare.\nLa Tua Risposta:");
                                                         scanf("\n%c", &salva);
                                                         while('\n'!=getchar());
                                                         if(max_prestiti < 3 && (salva == 'y' || salva == 'Y')){
                                                                *isbn = estrai_isbn(L2, titolo1, isbn);
                                                                *autore = estrai_autore(L2, titolo1, autore);
                                                                salva_prestito(nome,cognome,matricola1,titolo1,autore,isbn);
                                                                rimuovi_da_prestiti_sos(matricola1, isbn);
                                                                printf("\n==============================");
                                                                printf("\nPrestito Eseguito Con Successo.");
                                                                printf("\n==============================\n\n");
                                                                n_studenti = 0;
                                                        }else if(max_prestiti == 3 && (salva == 'y' || salva == 'Y')){
                                                                printf("\n==============================");
                                                                printf("\nAttenzione Lo Studente Ha Terminato I Prestiti Possibili.\nRetituire Uno Dei Libri Prima Di Effettuare Un Nuovo Prestito.");
                                                                printf("\n==============================\n\n");
                                                                rimuovi_da_prestiti_sos(matricola1, titolo1);
                                                                n_studenti -= 1;
                                                        }else if(salva == 'n' || salva == 'N'){
                                                                rimuovi_da_prestiti_sos(matricola1, isbn);
                                                                n_studenti -= 1;
                                                        }
                                                    }while(n_studenti != 0);
                                                }
                                            }else if(n_restituiti == n_prestiti){
                                                printf("\n==============================");
                                                printf("\nAttenzione Restituzione Fallita Matricola Studente O Titolo Libro Inseriti Errati.");
                                                printf("\n==============================\n\n");
                                            }

                                        }
                                    }else{
                                        printf("\n==============================");
                                        printf("\nNon Esistono Prestiti Al Momento.");
                                        printf("\n==============================\n\n");
                                    }
                                break;
                                }
							}else if(max_prestiti == 3 && n_richiesta == 1){
                                                printf("\n==============================");
                                                printf("\nAttenzione Lo Studente Ha Terminato I Prestiti Possibili.\n Retituire Uno Dei Libri Prima Di Effettuare Un Nuovo Prestito.");
                                                printf("\n==============================\n\n");
                                    }
							}while((n_richiesta == 1 ||  n_richiesta == 2)  && !(richieste_piene(scelta1,dim)));
                    L1 = L1->next;
					}else {
                        printf("\n==============================");
                        printf("\nScelta Errata, Ritenta.");
                        printf("\n==============================\n\n");
                        }
					}
					break;
				case 2:
					do{
						scelta2 = menu_bibliotecario(scelta2);
						while('\n'!=getchar());
						switch (scelta2){
							case 1:
                                    i = 0;
                                    printf("\n==============================");
                                    printf("\nAggiungi Alla Libreria\n");
                                    printf("==============================\n\n");
									printf("Quanti Libri Vuoi Aggiungere Alla Libreria:");
                                    scanf("%d", &dimensione);
                                    while('\n'!=getchar());
                                    while(i<dimensione){
                                        printf("Inserire Il Titolo Del Libro:");
                                        fgets(titolo, 100, stdin);
                                        printf("Inserire L'Autore:");
                                        fgets(autore, 100, stdin);
                                        printf("Inserire ISBN:");
                                        fgets(isbn, 20, stdin);
                                        *titolo = pulisci_buff(titolo);
                                        *autore = pulisci_buff(autore);
                                        *isbn = pulisci_buff(isbn);
                                        L2 = inserisci_libro(L2,titolo,autore, isbn);
                                        i++;
                                    }
                                    n_richieste_sospese = 0;
                                    max_prestiti = 0;
                                    n_richieste_sospese = verifica_richieste_aggiunta_libro(titolo, isbn, n_richieste_sospese);
                                    *matricola1 = estrai_matricola_da_aggiunta(titolo, isbn, matricola1);
                                    max_prestiti = verifica_Max_prestiti(matricola1, max_prestiti);
                                    if(n_richieste_sospese > 0){
                                        *nome = estrai_nome_da_aggiunta(matricola1,nome);
                                        *cognome = estrai_cognome_da_aggiunta(matricola1, cognome);
                                        printf("Attenzione Lo Studente: %s %s Aveva Richiesto Il Libro %s.\nEffettuare La Richiesta Di Prestito A Suo Nome:", nome, cognome,titolo);
                                        printf("\nY)Per Confermare;\nN)Per Rifiutare.\nLa Tua Risposta:");
                                        scanf("\n%c", &salva);
                                     while('\n'!=getchar());
                                     if(max_prestiti < 3 && (salva == 'y' || salva == 'Y')){
                                            *isbn = estrai_isbn(L2, titolo, isbn);
                                            *autore = estrai_autore(L2, titolo, autore);
                                            salva_prestito(nome,cognome,matricola1,titolo,autore,isbn);
                                            rimuovi_da_libri_inesistenti(matricola1, titolo, isbn);
                                            printf("\n==============================");
                                            printf("\nPrestito Eseguito Con Successo.");
                                            printf("\n==============================");
                                            printf("\n\n");
                                    }else if(max_prestiti == 3 && (salva == 'y' || salva == 'Y')){
                                            printf("\n==============================");
                                            printf("\nAttenzione Lo Studente Ha Terminato I Prestiti Possibili.\nRetituire Uno Dei Libri Prima Di Effettuare Un Nuovo Prestito.");
                                            printf("\n==============================\n\n");
                                    }
                                }
								break;
                            case 2:
                                        elimina = 0;
                                        printf("\n==============================");
                                        printf("\nElimina Dalla Libreria\n");
                                        printf("==============================\n\n");
                                        printf("Inserire Il Titolo Del Libro Da Eliminare:");
                                        fgets(titolo, 100, stdin);
                                        printf("Inserire ISBN Del Libro Da Eliminare:");
                                        fgets(isbn, 20, stdin);
                                        *titolo = pulisci_buff(titolo);
                                        *isbn = pulisci_buff(isbn);
                                        elimina = elimina_da_biblioteca(titolo, isbn, elimina);
                                        if(elimina == 0){
                                             printf("\n==============================");
                                             printf("\nAttenzione Eliminazione Fallita ISBN O Titolo Libro Inseriti Errati.");
                                             printf("\n==============================\n\n");
                                        }else if(elimina == 1){
                                             printf("\n==============================");
                                             printf("\n Eliminazione Avvenuta Con Successo.");
                                             printf("\n==============================\n\n");
                                        }else if(elimina == 2){
                                             printf("\n==============================");
                                             printf("\nAttenzione Impossibile Eliminare Libro In Prestito.");
                                             printf("\n==============================\n\n");
                                        }
                                    break;
                            case 3:
                                do{
                                    v_r=menu_richieste_sospese(v_r);
                                    while('\n'!=getchar());
                                    switch(v_r){
                                        case 1:
                                                n_richieste_sospese = 0;
                                                n_richieste_sospese = stato_sospesi(n_richieste_sospese);
                                                if(n_richieste_sospese == 0){
                                                    printf("\n==============================");
                                                    printf("\nNon Esistono Richieste Di Prestito In Sospeso.");
                                                    printf("\n==============================\n\n");
                                                }else{
                                                    printf("\n==============================");
                                                    printf("\nFine Lista Richieste Sospese.");
                                                    printf("\n==============================\n\n");
                                                }
                                                break;
                                        case 2:
                                                n_richieste_libri_inesistenti = 0;
                                                n_richieste_libri_inesistenti = stato_non_presenti(n_richieste_libri_inesistenti);
                                               	if(n_richieste_libri_inesistenti == 0){
                                                    printf("\n==============================");
                                                    printf("\nNon Esistono Richieste Di Aggiunta Di Libri.");
                                                    printf("\n==============================\n\n");
                                                }else{
                                                    printf("\n==============================");
                                                    printf("\nFine Lista Richieste Di Aggiunta.");
                                                    printf("\n==============================\n\n");
                                                }
                                                break;
                                        case 3:
                                                printf("\n==============================");
                                                printf("\nHai Deciso Di Tornare Al Menu' Precedente.");
                                                printf("\n==============================\n\n");
                                                break;
                                        default:
                                                printf("\n==============================");
                                                printf("\nScelta Errata, Ritenta.");
                                                printf("\n==============================\n\n");
                                                break;
                                    }
                                }while((v_r != 1 ||  v_r != 2) && v_r != 3);
                                break;
							case 4:
                                printf("\n==============================");
                                printf("\nHai Deciso Di Tornare Al Menu' Precedente.");
                                printf("\n==============================\n\n");
								break;
							default:
                                printf("\n==============================");
                                printf("\nScelta Errata, Ritenta.");
                                printf("\n==============================\n\n");
								break;
						}
					}while((scelta2 != 1 ||  scelta2 != 2 ||  scelta2 != 3) && scelta2 != 4);
					break;
				case 3:
				    if (j == 0){
                        stampa_libreria(L2);
                        j++;
				    }else{
                        Libreria *L2 = NULL;
                        L2=leggi_da_file(L2);
                        stampa_libreria(L2);
				    }
					printf("\n==============================");
					printf("\nFine Libreria.");
					printf("\n==============================\n\n");
					break;
				case 4:
				    n_prestiti1 = 0;
					n_prestiti1 = stato_prestiti(n_prestiti1);
					if(n_prestiti1 == 0){
                    printf("\n==============================");
					printf("\nNon Esistono Prestiti Al Momento.");
					printf("\n==============================\n\n");
					}else{
                    stampa_prestiti();
                    printf("\n==============================");
					printf("\nFine Lista Prestiti.");
					printf("\n==============================\n\n");
					}
					break;
				case 5:
                    printf("\n==============================");
					printf("\nHai Deciso Di Uscire.");
					printf("\n==============================\n\n");
					break;
				default:
                    printf("\n==============================");
					printf("\nScelta Errata, Ritenta.");
					printf("\n==============================\n\n");
					break;
			}
		}while((scelta_ini != 1 ||  scelta_ini != 2 || scelta_ini != 3 ||  scelta_ini != 4) && scelta_ini != 5);
	printf("\nSei Sicuro Di Voler Uscire Dal Programma?\n\n\tY)Per Terminare;\n\tN)Per Continuare;\n\nLa Tua Risposta:");
	scanf("\n%c",&loop);
	}
	L1 = dealloca_lista_studenti(L1);
	L2 = dealloca_libreria(L2);
	return 0;
}
