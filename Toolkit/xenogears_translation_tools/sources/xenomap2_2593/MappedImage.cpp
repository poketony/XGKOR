// MappedImage.cpp: implementation of the CMappedImage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xenomap.h"
#include "MappedImage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMappedImage::CMappedImage()
{

}

CMappedImage::~CMappedImage()
{

}

CMappedImage::CMappedImage(const CMappedImage& InitMap){
	m_array.SetSize(InitMap.m_array.GetSize());
	for (int i=0; i <InitMap.m_array.GetSize(); i++)
		m_array.SetAt(i,  InitMap.m_array.GetAt(i));
}

INT CMappedImage::setData(BYTE *data)
{
	DWORD size;
	m_array.RemoveAll();
	
	memcpy(&size, data, 4);
	m_array.SetSize(size);
	CMapData md;

	for (UINT i=0; i<size; i++){
		md.setData(data + 4 + 0x1C * i);
		m_array.SetAt(i, md);
	}
	
	return size;
}

CMapData CMappedImage::getAt(UINT nIndex)
{
	return m_array.GetAt(nIndex);
}



UINT CMappedImage::getData(BYTE *data)
{
	DWORD size;
	size = m_array.GetSize();	
	memcpy(data, &size, 4);

	for (UINT i=0; i<size; i++){
		BYTE mapdata[0x1c];
		m_array[i].getData(mapdata);
		memcpy(data+4+0x1C*i,mapdata,0x1C);
	}
	return size*0x1C+4;
}

UINT CMappedImage::getSize()
{
	return m_array.GetSize();
}

void CMappedImage::setAt(UINT nIndex, CMapData md)
{
	m_array.SetAt(nIndex, md);
	return;
}

INT CMappedImage::Add(CMapData md)
{
	return m_array.Add(md);
}

void CMappedImage::RemoveAt(UINT nIndex, UINT nCount)
{
	m_array.RemoveAt(nIndex,nCount);
}

CMappedImage CMappedImage::operator=(CMappedImage& md)
{
	BYTE* data;
	data = new BYTE[md.getSize() * 0x1c+4];
	md.getData(data);
	this->setData(data);
	delete[] data;
	return *this;
}

UINT CMappedImage::getLength()
{
	return getSize()*0x1c+4;
}
