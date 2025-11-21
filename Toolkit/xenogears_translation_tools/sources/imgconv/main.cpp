#include <stdio.h>
#include <string.h>

#include "tile.h"

int main(int argc, char* argv[]){

	FILE* file;
	
	if (argc!=4){
		printf("ImgConv 1.0 by chop\n");
		printf("Utilizzo:");
		printf("\timgcomv [-48|-84] src.raw dst.raw\n");
		printf("Converte da 4bpp a 8bpp o viceversa\n");
		return 0;
	}

	file=fopen(argv[2], "rb");
	if (file == NULL)
		return 0;

	unsigned char* buffer;

	fseek(file, 0, SEEK_END);
	long len = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char *data;

	buffer = new unsigned char[len];
	fread(buffer, len, 1, file);
	fclose (file);

	if (strcmp(argv[1], "-84")==0){
		data = new unsigned char[len*2];

		CTile tile(len*2,1);

		tile.setData(buffer, TILE_MODE_4BPP);
		tile.getData(data);

		file = fopen(argv[3], "wb");
		fwrite(data,len*2,1,file);
		fclose(file);
		delete[] data;
	}
	else if (strcmp(argv[1], "-48")==0){
		data = new unsigned char[len/2];

		CTile tile(len,1);

		tile.setData(buffer, TILE_MODE_8BPP);
		tile.getData(data, TILE_MODE_4BPP);

		file = fopen(argv[3], "wb");
		fwrite(data,len/2,1,file);
		fclose(file);
		delete[] data;
	}
	else
		printf("Parameter unknown %s\n", argv[1]);

	return 1;



}