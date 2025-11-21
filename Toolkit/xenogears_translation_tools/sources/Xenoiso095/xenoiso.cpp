// xenoiso.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"
#include "ArchiveIndex.h"
#include "Commandlist.h"
#include "IsoManager.h"

#define TRUE -1
#define FALSE 0

unsigned long FindEndOfIndex(unsigned char* index, unsigned long maxsize);
unsigned long SizeToSectors(unsigned long size, int secsize);

int glb_VideoFiles;
int glb_FirstNonVideoSector;
int glb_IndexSector2;
int glb_debug;
FILE* log;
int _tmain(int argc, _TCHAR* argv[])
{
	
	glb_debug = FALSE;

	if ((argc<2)||(argc>3)){
		printf("Xenoiso v0.95 by chop\r\n");
		printf("Istruzioni:\r\n");
		printf("\txenoiso list.txt [-d]\r\n");
		printf("list.txt \212 un file di testo che contiene informazioni sui file da sostituire\r\n");
		printf("Vedere xenoiso.txt per informazioni dettagliate sul file list.txt\r\n");
		printf("\r\nwww.sadnescity.it\r\n");
		return 0;
	}

	if (argc == 3){
		if(strcmp(argv[2],"-d")==0){
			glb_debug=TRUE;
			printf("Modalit\133 Debug\r\nViene creato un log nel file log.txt\r\n");	
			log = fopen("log.txt", "wt");
			if (log==NULL) {printf("Errore apertura log\r\n");return 0;}
		}
		else{
			printf("Xenoiso v0.95 by chop\r\n");
			printf("Istruzioni:\r\n");
			printf("\txenoiso list.txt [-d]\r\n");
			printf("list.txt \212 un file di testo che contiene informazioni sui file da sostituire\r\n");
			printf("Vedere xenoiso.txt per informazioni dettagliate sul file list.txt\r\n");
			printf("\r\nwww.sadnescity.it\r\n");
			return 0;
		}
	}

	if (glb_debug) fprintf(log,"Apertura file comandi\n");
	CCommandList cmd;
	FILE_ENTRY fe;
	switch (cmd.setList(argv[1])){
	case 1:
		glb_VideoFiles = 18;
		glb_FirstNonVideoSector = 108561;
		glb_IndexSector2 = 108607;
		if (glb_debug) fprintf(log,"Numero file video:%d\nPrimo settore non video:%d\nSettore indice:%d\n",glb_VideoFiles,glb_FirstNonVideoSector,glb_IndexSector2);
		break;
	case 2:
		glb_VideoFiles = 14;
		glb_FirstNonVideoSector = 172873;
		glb_IndexSector2 = 172919;
		if (glb_debug) fprintf(log,"Numero file video:%d\r\nPrimo settore non video:%d\r\nSettore indice:%d\r\n",glb_VideoFiles,glb_FirstNonVideoSector,glb_IndexSector2);
		break;
	case 0:
		printf("!!!Errore nell'apertura del file %s\n", argv[1]);
		if (glb_debug) fprintf(log,"Errore Apertura file\n");
		return 0;
	case -1:
		printf("Tipo CD sconosciuto");
		if (glb_debug) fprintf(log,"!!!Tipo CD sconosciuto\n");
		return 0;
	}



	char src[100];
	char dst[100];
	cmd.getSrc(src);
	cmd.getDst(dst);

	CIsoManager s, d;

	//Apri e crea l'iso
	if (glb_debug) fprintf(log,"Apertura iso originale %s\n", src);
	if (!s.OpenIso(src)){
		printf("Errore nell'apertura del file %s\r\n", src);
		if (glb_debug) fprintf(log,"!!!Errore nell'apertura iso originale\n");
		return 0;
	}
	if (glb_debug) fprintf(log,"Apertura Iso Destinazione %s\n", dst);
	d.CreateIso(dst);

	printf("Lettura indice... ");
	if (glb_debug) fprintf(log,"Lettura Indice\n");
	//Leggi l'indice
	CArchiveIndex index;
	CArchiveIndex index2;
	index.SetFileToSkip(glb_VideoFiles);
	index2.SetFileToSkip(glb_VideoFiles);
	unsigned char indice[32768];
	memset(indice,0,32768);
	s.Read(indice, 24, 16);
	unsigned long indexsize=FindEndOfIndex(indice, 32768);
	if (!index.ReadIndex(indice,indexsize)){
		printf("Errore nella lettura dell'indice\r\n");
		if (glb_debug) fprintf(log,"!!!Errore nella lettura dell'indice del primo file\n");
		return 0;
	}
	if (!index2.ReadIndex(indice,indexsize)){
		printf("Errore nella lettura dell'indice\r\n");
		if (glb_debug) fprintf(log,"!!!Errore nella lettura dell'indice del secondo file\n");
		return 0;
	}
	printf("Fatto!\r\n");



	printf("Aggiornamento indice...");
    //Leggi e aggiorna i file
	if (glb_debug) fprintf(log,"Aggiornamento indice\n");

	int num = 0; char path[100];
	while(cmd.getNextFile(&fe) != NULL){
		if (glb_debug) fprintf(log,"Sostituzione file %s in posizione %d\n", fe.path, fe.num);
		if (!index2.setNewPath(fe.num, fe.path)){
			printf("Errore nell'apertura del file %s\r\n", fe.path);
			if (glb_debug) fprintf(log,"!!!Errore nella sostituzione del file %s\n",fe.path);
			return 0;
		}
	}

	printf("Fatto!\r\n");
	if (glb_debug){
		printf("Continuare con la creazione dell'iso? [y,n]");
		if (getchar() != 'y') return 0;
	}

	printf("Copia dei filmati...");
	if (glb_debug) fprintf(log,"Copia dei filmati\n");

	//Copia i primi 108561 settori (boot e filmati)
	int i=0;
	unsigned char tbuffer[32*2352];


	for (i=0; i<glb_FirstNonVideoSector-32; i+=32)
	{
		s.ReadRawSectors(tbuffer, i, 32);
		d.AppendRawSectors(tbuffer, 32);
	}
	s.ReadRawSectors(tbuffer, i, glb_FirstNonVideoSector-i);
	d.AppendRawSectors(tbuffer, glb_FirstNonVideoSector-i);
	printf("Fatto!\r\n");


	//Leggi l'indice dal file numero glb_VideoFiles (i precedenti sono STR -non supportati-)
	//e inseriscii file nella nuova iso
	indexsize = index.getIndexLength();
	for (i=glb_VideoFiles; (unsigned)i <indexsize; i++){
		printf("Scrittura file %d...",i);

		if (index2.getType(i)==TYPE_FILE){
			if (!index2.getChangedFlag(i)){
				//file non modificato => copialo dall'indice non modificato
				int length = index.getSize(i);	
				int len_sec = SizeToSectors(length,2048);
				for (int cc=0; cc<len_sec-32; cc+=32){
					s.Read(tbuffer, index.getSector(i) + cc, 32);///!!!
					d.Append(tbuffer, 32);
				}
				s.Read(tbuffer, index.getSector(i) + cc, len_sec-cc);
				d.Append(tbuffer, len_sec-cc);
				if (glb_debug) fprintf(log,"Scrittura file non modificato %d\n",i);
			}
			else{
				//file modificato
				FILE* newfile;
				index2.getNewPath(i,path);
				if (glb_debug) fprintf(log,"Sostituzione file %d con %s\n",i,path);
				newfile = fopen(path,"rb");
				if (newfile == NULL){
					printf("Errore nell'apertura del file %s\r\n", path);
				if (glb_debug) fprintf(log,"!!!Errore nell'apertura del file %s\n",path);
				return 0;
				}
				fseek(newfile, 0, SEEK_END);
				int length = ftell(newfile);
				int len_sec = SizeToSectors(length,2048);
				fseek(newfile,0,SEEK_SET);

				for (int cc=0; cc<len_sec-32; cc+=32){
					fread(tbuffer,2048*32,1,newfile);
					d.Append(tbuffer, 32);
				}
				fread(tbuffer,length-(cc*2048),1,newfile);
				d.Append(tbuffer, (len_sec-cc));
				fclose(newfile);
			}
			
		}
		printf("Fatto!\r\n");
	}

	printf("Scrittura indice...");
	if (glb_debug) fprintf(log,"Scrittura Indice\r\n");

	//Scrivi Indice
	memset(indice,0,32768);
	index2.WriteIndex(indice, &indexsize);
	d.Write(indice,24,16);
	memset(indice,0xFF,4);
	index2.WriteIndex(indice+4, &indexsize);
	d.Write(indice,glb_IndexSector2,16);
	printf("Fatto!\r\n");


	//fine
	printf("Operazione eseguita con successo\r\n");
	if (glb_debug) fprintf(log,"Esecuzione terminata");
	if (glb_debug) fclose(log);

	return 0;
}



unsigned long FindEndOfIndex(unsigned char* index, unsigned long maxsize){
	//
	//Dato l'indice ne trova la dimensione effettiva
	//(conta tutti i byte fino a trovare un entry con 0xFFFFFF come primi 3 byte)
	//

	unsigned long i=0;
	while(i < maxsize){
		if ((index[i] == 0xFF) && (index[i+1]==0xFF) && (index[i+2]==0xFF))
			return i+7;
		i+=7;
	}
	return 0;
}



unsigned long SizeToSectors(unsigned long size, int secsize)
{
	/**
	 **Converte una lunghezza in numero di settori
	 **/
	unsigned long temp;
	temp=size/secsize;
	if(size%secsize != 0) temp++;
	return temp;
}
