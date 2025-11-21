/*

Mat - 27/12/2004
E-mail: mattia.d.r@libero.it
Sito:   http://www.matzone.altervista.org
Membro dei SadNES cITy: http://www.sadnescity.it
*/

#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <string.h>
#define MAXDIR 256
#define BUFFSIZE 32768

int crea_archivioAFS(FILE *dest, char *(*origN), unsigned int numfile);
/* Crea un archivio di Xeonogears
    dest:    file pointer dell'archivio da creare (aprire in "wb")
    origN:   array di stringhe contenente il nome dei file da aggiungere all'archivio
    numfile: numero di file da aggiungere all'archivio
    
    Valore di ritorno:
    0 in caso di successo
    1 in caso di errori di scrittura o di seek dell'archivio
    > 1 quando un file ha provocato errori in lettura (ritorna l'indice + 2
      del file che ha provocato errori in lettura nell'array origN)
    
    NOTA: La funzione non chiude il file pointer passato e cambia il seek
*/

int estrai_archivioAFS(FILE *arc, FILE *out);
/* Estrae un archivio di Xeonogears, scrivendo su out il nome dei file
   estratti e alcuni errori
    arc: file pointer dell'archivio da creare (aprire in "rb")
    out: file pointer su cui verranno scritti i messaggi, se 0 non stampa messaggi
    
    Valore di ritorno:
    0 in caso di successo
    1 se il file non e' un archivio
    2 in caso di errore di lettura o di seek
    3 in caso di errore di lettura dall'archivio di uno specifico file (messaggio su out)
    4 nel caso che sia impossibile creare un file (messaggio su out)
    5 in caso si errore di scrittura di un file (messaggio su out)
    
    NOTA: La funzione non chiude i file pointer passati e muove il seek
*/

int main(int argc, char *argv[]) {

   int err = 1;
   FILE *arc;
   
   if(argc >= 3) {  // Se ci sono almeno 3 argomenti
 
      if((argc <= 4) && (!strcmpi(argv[1], "-e"))) {  // Estrazione di un archivio
         char old_dir[MAXDIR];

         if((arc = fopen(argv[2], "rb")) == NULL) {  // apre l'archivio
            printf("Impossibile aprire il file %s - Operazione non riuscita\n", argv[2]);
            exit(2);  // uscita con errore
         }
         
         if(argc == 4) {  // se abbio specificato la dir destinazione
            if(!getcwd(old_dir, MAXDIR)) {  //ottime la dir corrente
               printf("Impossibile ottenere la directory corrente - Operazione non riuscita\n");
               exit(2);  // uscita con errore
            }
            mkdir(argv[3]);  // prova a creare la dir destinazione
            if(chdir(argv[3])) {  // entra nella dir destinazione
               printf("Impossibile entrare nella directory destinazione - Operazione non riuscita\n");
               exit(2);  // uscita con errore
            }
         }
         err = estrai_archivioXeno(arc, stdout);  // estrae l'archivio
         fclose(arc);  // chiude l'archivio
         if(argc == 4) chdir(old_dir);  // ripristina la dir iniziale
         if(err) {  // se ci sono errori
            if(err == 2) printf("Errore di lettura nell'archivio");
            // negli altri casi il messaggio e' stampato dalla funzione
            printf(" - Operazione non riuscita\n");
            exit(2);  // uscita con errore
         }
      }
      
      else if((argc >= 4) && (!strcmpi(argv[1], "-c"))) {  // Creazione archivio
         
         if((arc = fopen(argv[2], "wb")) == NULL) { // Crea if file archivio 
            printf("Impossibile creare il file %s - Operazione non riuscita\n", argv[2]);
            exit(2);  // uscita con errore
         }
         
         err = crea_archivioXeno(arc, argv + 3, argc - 3);  // crea l'archivio
         fclose(arc);  // chiude l'archivio
         if(err) {  // se c'e' un errore
            if(err == 1) printf("Impossibile scrivere il file %s", argv[2]);
            else if(err == -1) printf("Errore nell'allocazione della memoria");
            else printf("Impossibile leggere il file %s", argv[err + 1]);
            unlink(argv[2]);  // elimina l'archivio corrotto
            printf(" - Operazione non riuscita\n");
            exit(2);  // uscita con errore
         }
      }
   }
   
   if(err) {  // se non abbiamo digitato un parametro corretto
      printf("Xeno archive extractor/creator 0.1beta by Mat - USO:\nextXeno -e archivio [destinazione]   (estrae i file in un archivio)\nextXeno -c archivio file1 file2 file3 ...   (ricrea un archivio)\n\nMat - 27/12/2004\nE-mail:\tmattia.d.r@libero.it\nSito:\thttp://www.matzone.altervista.org\nMembro dei SadNES cITy: http://www.sadnescity.it\n");
      exit(1);  // uscita con errore per mancanza di parameti
   }
   printf("Xeno archive extractor/creator 0.1beta by Mat - Operazione riuscita\n"); // uscita normale
   exit(0);  // uscita corretta
}

int estrai_archivioXeno(FILE *arc, FILE *out) {
   unsigned int offset, size, blocco, numfile, count;
   char nomefile[13], buffer[BUFFSIZE];
   FILE *dest;

   if(fseek(arc, 0, SEEK_SET)) return 2;  // va all'inizio
   if(fread(&numfile, 4, 1, arc) != 1) return 2;  // legge in numero di file
   
   for(count = 0; count < numfile; ++count) {  //  cicla per tutti i file
      if(fseek(arc, 4 + (count << 2), SEEK_SET)) return 2;  // va nell'entrata del file
      if((fread(&offset, 4, 1, arc) + fread(&size, 4, 1, arc)) != 2) return 2;
      size -= offset; // calcola la grandezza del file
      if(fseek(arc, offset, SEEK_SET)) return 2;  // si posiziona dov'e' il contenuto del file
      sprintf(nomefile, "%.2d.xen", count + 1);  // il nome del file e' uguale a count + 1
      if((dest = fopen(nomefile, "wb")) == NULL) {  // crea il file destinazione
         if(out) fprintf(out, "Impossibile creare il file %s", nomefile);
         return 4;
      }
      if(out) fprintf(out, "%s -%6d byte\n", nomefile, size);  // scrive il nome del file
      while(size > 0) {  // cicla finche' ci sono dati da leggere
         if(size < BUFFSIZE) blocco = size;  // ci sono da leggere meno dati della grandezza del buffer
         else blocco = BUFFSIZE;  // dati maggiori della grandezza del buffer
         if(fread(buffer, 1, blocco, arc) != blocco) {  // legge un blocco dati
            fclose(dest);
            unlink(nomefile);
            if(out) fprintf(out, "Impossibile leggere il file %s dall'archivio", nomefile);
            return 3;
         }
         if(fwrite(buffer, 1, blocco, dest) != blocco) {// scrive un blocco dati
            fclose(dest);
            unlink(nomefile);
            if(out) fprintf(out, "Impossibile scrivere il file %s", nomefile);
            return 5;
         }  
         size -= blocco;  // diminuisce i dati ancora da scrivere
      }
      fclose(dest);  // chiude il file destinazione
   }
   return 0;
}

int crea_archivioXeno(FILE *dest, char *(*origN), unsigned int numfile) {
   // i file vanno posizionati all'inzio di un blocco
   char buffer[BUFFSIZE];
   FILE *orig;
   unsigned int i, nbyte, offset;  // coppia offeset-grandezza
    
   if(fseek(dest, 0, SEEK_SET)) return 1;  // inzio dell'archivio
   if(fwrite(&numfile, 4, 1, dest) != 1) return 1;  // scrive l'inizio del file
   if(fwrite(buffer, 4 + (numfile << 2), 1, dest) != 1) return 1;  // lascia spazio per la tabella dei puntatori
   
   for(i = 0; ; ++i) {  // per tutti  i file
      if((offset = ftell(dest)) == -1) return 1;  // salva l'offset del file
      if(fseek(dest, 4 + (i << 2), SEEK_SET)) return 1;  // si posizione nell'entata della tabella dei file
      if(fwrite(&offset, 4, 1, dest) != 1) return 2;  // scrive l'offset del file
      if(fseek(dest, offset, SEEK_SET)) return 1;  // ritorna nella posizone iniziale
      if(i >= numfile) break; // condizione di uscita
      if((orig = fopen(origN[i], "rb")) == NULL) return i + 2;  // apre il file
      while((nbyte = fread(buffer, 1, BUFFSIZE, orig)) > 0) {  // legge il file
         if(fwrite(buffer, nbyte, 1, dest) != 1) {fclose(orig); return 1;}  // scrive l'achivio
      }
      if(ferror(orig)) return i + 2;  // se ce stato errore in lettura
      fclose(orig);
   }
   /*
   offset %= 8;
   if(offset) {
       offset = 8 - offset;
       memset(buffer, 0, offset);
       if(fwrite(buffer, offset, 1, dest) != 1) return 2;
   }   */
   memset(buffer, 0, 4);
   if(fwrite(buffer, 4, 1, dest) != 1) return 2;
   return 0;  // fine con successo
}

