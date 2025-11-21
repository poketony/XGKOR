////////////////////////////////////////////////////////////////////
//XenoComp beta by Chop_                                          //
//ANSI C                                                          //
//                                                                //
//This program will decompress some files in the Xenogears CD     //
//                                                                //
//(c) chop_ 2003                                                  //
////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<string.h>

#define	N			4096
#define F			18
#define THRESHOLD	3

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef int INT;

int decomp(FILE* file, FILE* dest);
int comp(FILE* file, FILE* dest);
int lzss_Search(BYTE *MemBuff, BYTE *ReadBuff, int *pos, UINT r, UINT nReadEnd);
int lzss_Search(BYTE* pData, UINT nCurrent, UINT nMax, int *nFind);

int main(int argc, char *argv[]){
	
	printf("Xenocomp v2 by chop_\n"
		   "Xenogears Main Decompressor\n\n");
	//
	//Verifica Parametri
	//
	//Release
	if (argc != 4) {
		printf("'xenocomp -d file1 file2' decompress file1 into file2.\n");
		printf("'xenocomp -c file1 file2' compress file1 into file2.\n");
		return -1;
	}
	

	//
	//Apre il file da decomprimere e il file destinazione
	//
	FILE* file;
	FILE* dest;
	//Release
	file = fopen(argv[2], "rb");
	dest = fopen(argv[3], "wb");
	if ((file == NULL) || (dest == NULL)){
		printf("File Open Error");
		return -1;
	}

	if (strcmp(argv[1], "-d") == 0){
		printf("Decompressing file %s\n", argv[2]);
		decomp(file, dest);
	}
	else if (strcmp(argv[1], "-c") == 0){
		printf("Compressing file %s\n", argv[2]);
		comp(file, dest);
	}
	else{
		printf("Unknown command %s\n", argv[2]);
	}

/*	//dbg
	file = fopen("0029d", "rb");
	dest = fopen("0029c", "wb");
	if ((file == NULL) || (dest == NULL)){
		printf("File Open Error");
		return -1;
	}
	comp(file,dest);
*/
	fclose(file);
	fclose(dest);
	return 1;
}

int decomp(FILE* file, FILE* dest){

	//
	//Decompressione
	//
	BYTE txtbuff[N];
	//BYTE readahead[F]; //non serve per decomprimere!
	int r = 0;
	for (int i = 0; i < N - F; i++) txtbuff[i++] = 0;
	r = N - F;
		
	//
	//Leggi la lungh del file decompresso
	//
	long decomplength = 0;
	fread(&decomplength, 4 , 1, file);

	
	//
	//Inizio decompressione
	//

	while (ftell(dest) < decomplength){
		//
		//Leggi la flag
		//
		BYTE	flag;
		fread(&flag, 1, 1, file);
		//
		//Leggi tutti gli 8 bit della flag per capire se ho 
		//testo compresso o no.
		//Si parte dal bit meno significativo.
		//
		BYTE	shift = 0;
		for(shift = 0; (shift < 8) ; shift++){
			if ((flag & (1 << shift)) == 0){
				//Non compresso.
				//Copio un byte in uscita e nel memory buffer
				BYTE temp = 0;
				fread(&temp, 1, 1, file);
				fwrite(&temp ,1 ,1, dest);
				txtbuff[r++] = temp;
				r &= N - 1;
			}
			else{
				//Compresso
				//Leggo due byte e calcolo posizione e lunghezza
				//Formato: 7P 6P 5P 4P 3P 2P 1P 0P | 3L 2L 1L 0L 11P 10P 9P 8P
				BYTE temp = 0;
				WORD pos = 0;
				BYTE length = 0;
				
				//Genera posizione e lunghezza
				fread(&temp, 1, 1, file);
				pos = temp;
				fread(&temp, 1, 1, file);
				pos |= ((temp & 0x0f) << 8);
				length = ((temp &0xf0) >> 4) + THRESHOLD;

				//Copia length byte in uscita e nel memory buffer
				for (i = 0; i < length; i++){
					temp = txtbuff[(r - pos) & (N - 1)];
					fwrite(&temp, 1, 1, dest);
					txtbuff[r++] = temp;
					r &= N - 1;
				}
			
			}

		}
	}
	printf("Decompression done!\n");
	printf("Output file lengh %ld should be %ld", ftell(dest), decomplength);
	
	return 1;

}

int comp(FILE* file, FILE* dest){
	//
	//Comprime il buffer pData creando un nuovo buffer e riscrivendolo
	//nel buffer m_pFileData
	//

	BYTE	MemoryBuff[N];
	BYTE	ReadAhead[F];
	int		r = 0;
	memset(MemoryBuff, 0, N);
	memset(ReadAhead, 0, F);

	
	UINT nDecompPos = 0;
	fseek(file, 0, SEEK_END);
	UINT nDecompLength = ftell(file);
	fseek(file, 0, SEEK_SET);

	BYTE* pDecData;
	pDecData = new BYTE[nDecompLength];
	fread(pDecData, nDecompLength, 1, file);

	//
	//Alloca un buffer temporaneo di lunghezza nDecompLength 
	//per contenere il file compresso
	//
	UINT nTempOffset = 0;
	BYTE* pTempData;
	pTempData = new BYTE[nDecompLength * 2];

	memset(pTempData, 0, nDecompLength * 2);
	nTempOffset = 4; //Salta i primi 4 byte (lunghezza fittizia file)
	UINT k =0;
	do{
		UINT nFlagPos = nTempOffset++;	//Salva la posizione della flag
		for (k = 0; (k < 8) && (nDecompPos < nDecompLength); k++){
			//Loop sugli 8 bite della flag
			
			if (nTempOffset > 3824)
				printf("");

			//
			//Carica il read ahead con al più i 18 byte seguenti
			//
			if ((UINT)ftell(file) > nDecompLength)
				printf("End of file\n");
			//fseek(file, nDecompPos, SEEK_SET);
			
			UINT nEndOfReadAhead = (nDecompPos + F > nDecompLength) ? (nDecompLength - nDecompPos) : F;
			memcpy(ReadAhead, pDecData + nDecompPos, nEndOfReadAhead);

			//
			//Effettua la ricerca sul memory buffer
			//
			BYTE nLungh = 0;
			int nSearchPos = 0;
			//nLungh = lzss_Search(MemoryBuff, ReadAhead, &nSearchPos, r, nEndOfReadAhead);
			nLungh = lzss_Search(pDecData, nDecompPos, nDecompLength, &nSearchPos);
			if ((char)nLungh == -1){
				//
				//Non ho trovato nulla nel memory buffer:
				//Copio un byte in uscita e nel memory buffer
				//
				pTempData[nTempOffset++] = ReadAhead[0];
				MemoryBuff[r++] = ReadAhead[0];
				r &= (N - 1);
				nDecompPos++;
			}
			else{
				//
				//Ho trovato qualcosa:
				//Copia puntatore-lunghezza in uscita e aggiorna il memory buffer
				//
				nSearchPos = (r - nSearchPos) & 0xFFF;
				pTempData[nFlagPos] |= (1 << k);
				pTempData[nTempOffset++] = (BYTE)(nSearchPos & 0x00FF);
				pTempData[nTempOffset] = (BYTE)((nSearchPos & 0x0F00) >> 8);
				pTempData[nTempOffset++] += (BYTE)(((nLungh - THRESHOLD) & 0x000F) << 4);

				for (UINT it = 0; it < nLungh; it++){
					MemoryBuff[r++] = ReadAhead[it];
					r &= (N - 1);
				}
				nDecompPos += nLungh;
			}


		}
	}while(nDecompPos < nDecompLength);
	

	//
	//Padda con degli 0 la fine del file
	//
	while (k != 8){
		nDecompPos++;
		k++;
	}

	
	//Scrivi la lunghezza fittizia del file all'inizio
	DWORD dwTemp = nDecompPos;
	memcpy(pTempData, &dwTemp, 4);

	fwrite(pTempData, nTempOffset, 1, dest);


	return 1;

}

int lzss_Search(BYTE *MemBuff, BYTE *ReadBuff, int *pos, UINT r, UINT nReadEnd)
{
	//
	//Ricerca in MemBuff il ReadBuff
	//
	int best_result = 0;
	UINT best_pos = 0;
	int temp_result = 0;
	UINT i = 0, j = 0, k = 0;

	for (i=0; i< r; i++){
		temp_result = 0;
		k = 0;
		do{
			if ((MemBuff[i + k] == ReadBuff[k]) && (((i + k) < r) || (i > r)))
				temp_result++;
			else
				break;
			k++;
		}while(k < nReadEnd);

		if (temp_result > best_result){
			best_result= temp_result;
			best_pos=i;
		}
	}
	
	if ((best_result>=THRESHOLD))
	{
		*pos =best_pos;
		return(best_result);
	}

	return -1;

}


int lzss_Search(BYTE* pData, UINT nCurrent, UINT nMax, int *nFind)
{
	//Ricerca v2

	//Determina il massimo valore di k
	INT maxk;
	maxk = nCurrent + F > nMax ? nMax - nCurrent : F; //nMax - 1 ???

	//Determina la posizione iniziale
	UINT nStart;
	nStart = (INT)nCurrent - (N-F) < 0 ? 0 : (nCurrent - (N-F));
	
	UINT nPos = nStart;
	INT best_pos = -1;
	INT best_length = THRESHOLD - 1;
	//Ricerca
	while (nPos < nCurrent)
	{
		INT k = 0;
		while ((pData[nPos + k] == pData[nCurrent + k]) && (k < maxk))
		{
			k++;
		}
		if (k > best_length)
		{
			best_length = k;
			best_pos = nPos;
		}
		nPos++;
	}

	if (best_pos != -1)
	{
		*nFind = (best_pos & (N - 1));
		return best_length;
	}
	else
		return -1;
}

