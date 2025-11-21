// MapData.h: interface for the CMapData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPDATA_H__651D436E_8371_11D9_916E_00E098852DE0__INCLUDED_)
#define AFX_MAPDATA_H__651D436E_8371_11D9_916E_00E098852DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMapData  
{
public:
	void setFlipY(BOOL bFlip);
	void setFlipX(BOOL bFlip);
	BOOL isFlippedY();
	BOOL isFlippedX();
	BOOL setUnknownData(CString string);
	BOOL setUnknownData(BYTE* data);
	BOOL setYOffsetScreen(UINT y);
	BOOL setXOffsetScreen(UINT x);
	BOOL setYOffsetImage(UINT y);
	BOOL setXOffsetImage(UINT x);
	BOOL setWidth(UINT width);
	BOOL setHeight(UINT height);
	UINT getUnknownData(BYTE* data);
	CPoint* getScreenPos(CPoint* point);
	short getYOffsetScreen();
	short getXOffsetScreen();
	CRect* getImageRect(CRect* rect);
	INT getHeight();
	INT getWidth();
	INT getYOffsetImage();
	INT getXOffsetImage();
	BOOL setData(BYTE* data);
	BOOL getData(BYTE* data);
	CMapData();
	virtual ~CMapData();
protected:
	BYTE m_data[0x1C];

};

#endif // !defined(AFX_MAPDATA_H__651D436E_8371_11D9_916E_00E098852DE0__INCLUDED_)
