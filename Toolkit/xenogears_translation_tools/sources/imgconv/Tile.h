// Tile.h: interface for the CTile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILE_H__7CA04520_9B8A_11D8_916E_00E098852DE0__INCLUDED_)
#define AFX_TILE_H__7CA04520_9B8A_11D8_916E_00E098852DE0__INCLUDED_

#include "Palette.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define TILE_MODE_8BPP 1
#define TILE_MODE_4BPP 2


class CTile  
{
protected:
	CPalette* m_palette;
	unsigned char* m_data;
	int h, w, size;
public:
	//Returns a 24bit raw tile
	unsigned char* getRGBData();
	
	//Set the tile data with a 8bit indexed data
	unsigned char* setData(unsigned char* data, int mode= TILE_MODE_8BPP);
	
	//Returns a 8bit indexed tile
	unsigned char* getData(unsigned char *data, int mode = TILE_MODE_8BPP);

	//Set a palette for the current tile
	CPalette* setPalette(CPalette* palette);
	
	//Get the palette for the current tile
	CPalette* getPalette();

	//Constructor
	CTile(int h, int w);
	virtual ~CTile();

};

#endif // !defined(AFX_TILE_H__7CA04520_9B8A_11D8_916E_00E098852DE0__INCLUDED_)
