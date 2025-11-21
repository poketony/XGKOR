#include <stdio.h>
#include <stdlib.h>
#include<memory.h>

#define HEADERLENGTH 0x3e

typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;

int deinterleave(BYTE* pData, DWORD length);
int ConvertiBMP(BYTE* pData, DWORD length, FILE* dst);

int main (int argc, char* argv[])
{
	FILE* src;
	FILE* dst;

	if (argc != 2)
	{
		printf("Usage: fontdump file1\n");
		return 0;
	}

	src = fopen(argv[1], "rb");
	if (src == NULL)
	{
		printf("Error opening file %s\n", argv[1]);
		return 0;
	}

	fseek(src, 0, SEEK_END);
	DWORD dwSize = ftell(src) - 14; //Salta Header
	fseek(src, 14, SEEK_SET);		//Salta Header
	
	//Leggi i dati
	BYTE* pData;
	pData = new BYTE[dwSize];
	fread(pData, dwSize, 1, src);
	fclose(src);

	deinterleave(pData, dwSize);

	dst = fopen("dest2.bmp", "wb");
	if (dst == NULL)
	{
		printf("Error opening file dest2");
		return 0;
	}
	ConvertiBMP(pData, dwSize, dst);
	fclose(dst);
	
	return 1;
}

int deinterleave(BYTE* pData, DWORD length){

	DWORD i = 0, j = 0;

	while (i < length)
	{
		BYTE tile[22];
		memcpy(tile, pData + i, 22);
		for (j=0; j<11; j++)
		{
			pData[i + j] = tile[j * 2];
			pData[i + 11 + j] = tile [(j * 2) + 1];
		}
		i+=22;
	}
	return 1;
}

int ConvertiBMP(BYTE* pData, DWORD length, FILE* dst)
{
	//n*m tile
	const int n = 23;
	const int m = 13;
	
	DWORD dwTemp = 0;
	BYTE header[HEADERLENGTH];
	memset(header, 0, HEADERLENGTH);

	//Sigla iniziale
	header[0] = 'B';
	header[1] = 'M';
	//File size
	dwTemp = length + HEADERLENGTH;
	memcpy(header + 0x2, &dwTemp, 4);
	//Bitmap offset
	dwTemp = HEADERLENGTH;
	memcpy(header + 0xA, &dwTemp, 4);
	//Bitamp info headersize
	dwTemp = 0x28;
	memcpy(header + 0xE, &dwTemp, 4);
	//Width
	dwTemp = n * 16;
	memcpy(header + 0x12, &dwTemp, 4);
	//Height
	dwTemp = -m * 11;
	memcpy(header + 0x16, &dwTemp, 4);
	//Planes
	dwTemp = 0;
	memcpy(header + 0x1A, &dwTemp, 2);
	//bbp
	dwTemp = 1;
	memcpy(header + 0x1C, &dwTemp, 2);
	//Compression
	dwTemp = 0;
	memcpy(header + 0x1E, &dwTemp, 4);
	//Bitamp size
	dwTemp = length + (length % 4);
	memcpy(header + 0x22, &dwTemp, 4);
	//HResolution
	dwTemp = 1;
	memcpy(header + 0x26, &dwTemp, 4);
	//VResolution
	dwTemp = 1;
	memcpy(header + 0x2A, &dwTemp, 4);
	//Colors
	dwTemp = 2;
	memcpy(header + 0x2E, &dwTemp, 4);
	//Important Colors
	dwTemp = 0;
	memcpy(header + 0x32, &dwTemp, 4);
	//Palette
	BYTE pal[4];
	pal[0] = 0xFF; pal[1] = 0xFF; pal[2] = 0xFF;
	memcpy(header + 0x36, pal, 4);

	fwrite(header, HEADERLENGTH, 1, dst);

	//Scrivi il file
	DWORD i = 0, j =0, k = 0;
	BYTE tiles[n * 22];	//N di tile per riga * lungh tile in byte
	
	for (k = 0; k < m ; k++)		//loop sui tile per riga
	{
		memcpy(tiles, pData + k * (n * 22), (n * 22));
		for (j=0; j<11; j++)		//loop sulle righe dei tile
		{
			for (i = 0; i < (n * 22); i+=11)	//loop sui tile
			{
				fputc(tiles[i + j], dst);
			}
		}
	}

	return 1;
}