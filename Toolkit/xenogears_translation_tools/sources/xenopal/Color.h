// Color.h: interface for the CColor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLOR_H__A9986CE0_994D_11D8_916E_00E098852DE0__INCLUDED_)
#define AFX_COLOR_H__A9986CE0_994D_11D8_916E_00E098852DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define COL_MODE_24RGB	1
#define COL_MODE_16TBGR 2
#define COL_MODE_24YUV	3

class CColor  
{
private:
	//Color components
	int r,g,b;
public:
	//Return true if the colors have the same components
	int equals(CColor* c);
	
	//Calculates the distance between 2 colors in a 3d space
	double distance(CColor* c);

	//Returns a vectro with the color components in the desired mode
	unsigned char* getColor(unsigned char* v, int mode);
	
	//Constructor
	CColor(unsigned char* v, int mode);
	
	//Deconstructor
	~CColor();

};

#endif // !defined(AFX_COLOR_H__A9986CE0_994D_11D8_916E_00E098852DE0__INCLUDED_)
