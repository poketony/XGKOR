// Palette.cpp: implementation of the CPalette class.
//
//////////////////////////////////////////////////////////////////////

#include "Palette.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPalette::CPalette(int size)
{
	m_size = size;
	colors = new CColor*[size];

	for(int i=0; i < m_size; i++)
		colors[i]=NULL;

}

CPalette::~CPalette()
{
	for(int i=0; i < m_size; i++)
		if (colors[i]!=NULL) delete colors[i];
}

CColor* CPalette::getColor(int i)
{
	return colors[i];
}


int CPalette::ReadPalette(unsigned char *buffer, int nCol, int mode)
{
	int i=0;

	if (nCol>m_size) return i;	//esce se maggiore del numero max di colori

	for (i=0; i<nCol;i++){
		switch(mode){
		case COL_MODE_24RGB:
		case COL_MODE_24YUV:
			colors[i] = new CColor(buffer+i*3, mode);
			break;
		case COL_MODE_16TBGR:
			colors[i] = new CColor(buffer+i*2, mode);
			break;
		}
	}

	return i;
}

int CPalette::FindColor(CColor *col)
{
	for(int i=0; i < m_size; i++){
		if (colors[i]!=NULL){
			if (colors[i]->distance(col)==0) return i;
		}
	}

	return -1;
}	


int CPalette::FindBestMatch(CColor* col)
{
	int best = -1;	//valore non valido
	double dist = 999;	//valore alto

	for(int i=0; i < m_size; i++){
		if (colors[i]!=NULL){
			double temp = 0;
			temp = colors[i]->distance(col);
			if (temp<dist) best = i;
		}
	}

	return best;
}
