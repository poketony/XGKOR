// MappedImage.h: interface for the CMappedImage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPPEDIMAGE_H__9C48F100_8401_11D9_916E_00E098852DE0__INCLUDED_)
#define AFX_MAPPEDIMAGE_H__9C48F100_8401_11D9_916E_00E098852DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>
#include "MapData.h"

class CMappedImage  
{
typedef CArray<CMapData, CMapData> CMapDataArray;


public:
	UINT getLength();
	CMappedImage operator=(CMappedImage& md);
	void RemoveAt(UINT nIndex, UINT nCount=1);
	INT Add(CMapData md);
	void setAt(UINT nIndex, CMapData md);
	UINT getSize();
	UINT getData(BYTE* data);
	CMapData getAt(UINT nIndex);
	INT setData(BYTE* data);
	CMappedImage();
	CMappedImage(const CMappedImage& InitMap);
	virtual ~CMappedImage();
protected:

	CMapDataArray m_array;
};

#endif // !defined(AFX_MAPPEDIMAGE_H__9C48F100_8401_11D9_916E_00E098852DE0__INCLUDED_)
