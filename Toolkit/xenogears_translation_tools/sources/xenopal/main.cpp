#include <stdio.h>
#include <string.h>
#include "Palette.h"
#include "Color.h"

#define N 15

int main(int argc, char* argv[]){

	FILE* file;
	if ((file=fopen(argv[1], "rb")) == NULL)
		return 0;

	long len;
	fseek(file,0,SEEK_END);
	len = ftell(file);
	fseek(file,0,SEEK_SET);

	unsigned char* buffer;
	buffer = new unsigned char[len];

	fread(buffer,len,1,file);
	fclose (file);

	CPalette* pal[N];

	for (int i=0; i<N; i++){
		pal[i] = new CPalette(256);
		pal[i]->ReadPalette(buffer+512*i, 256, COL_MODE_16TBGR);
		FILE* palfile;
		char palname[15];
		char palcol[30];
		sprintf(palname, "pal%d.pal", i);
		palfile = fopen(palname, "wt");
		sprintf(palcol, "JASC-PAL\n0100\n256\n");
		fwrite(palcol,strlen(palcol),1,palfile);

		for (int j = 0; j<256; j++){
			CColor* col;
			unsigned char rgb[3];
			col = pal[i]->getColor(j);
			col->getColor(rgb, COL_MODE_24RGB);
			sprintf(palcol, "%d %d %d\n", rgb[0], rgb[1], rgb[2]);
			fwrite(palcol, strlen(palcol),1, palfile);
		}
		fclose(palfile);
	}


	return 1;


}