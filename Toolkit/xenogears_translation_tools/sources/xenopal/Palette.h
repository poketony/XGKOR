// Palette.h: interface for the CPalette class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PALETTE_H__47393D60_9B67_11D8_916E_00E098852DE0__INCLUDED_)
#define AFX_PALETTE_H__47393D60_9B67_11D8_916E_00E098852DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Color.h"

class CPalette  
{
protected:
	//Vector of CColor pointers
	CColor** colors;

	//Size of the vector
	int m_size;

public:
	//Returns the number of the nearest color in the palette
	int FindBestMatch(CColor* col);

	//Returns the number of the color in the palette
	int FindColor(CColor* col);

	//Reads a palette from a palette file
	int ReadPalette(unsigned char* buffer, int nCol, int mode = COL_MODE_24RGB);
	
	//Get a color
	CColor* getColor(int i);
	
	//Constructor
	CPalette(int size);
	
	//deconstructor
	virtual ~CPalette();

};

#endif // !defined(AFX_PALETTE_H__47393D60_9B67_11D8_916E_00E098852DE0__INCLUDED_)
