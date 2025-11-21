// Tile.cpp: implementation of the CTile class.
//
//////////////////////////////////////////////////////////////////////

#include "Tile.h"
#include <stdio.h>
#include <memory.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTile::CTile(int h, int w)
{
	this->w=w;
	this->h=h;
	size = w*h;
	m_data = new unsigned char[size];
}

CTile::~CTile()
{
	if (m_data!=NULL) delete m_data;
}

CPalette* CTile::getPalette()
{
	return m_palette;
}

CPalette* CTile::setPalette(CPalette *palette)
{
	CPalette* old = m_palette;
	m_palette = palette;
	return old;
}

unsigned char* CTile::getData(unsigned char *data, int mode)
{
	switch (mode){
	case TILE_MODE_8BPP:
		memcpy(data, m_data, h*w);
		break;
	case TILE_MODE_4BPP:
		for (int i=0; i<h*w;i+=2){
			data[i/2] = (m_data[i]>>4) | (m_data[i+1]&0xF0);
		}
		break;

	}
	return data;

}

unsigned char* CTile::setData(unsigned char *data, int mode ) 
{
	switch (mode){
	case TILE_MODE_8BPP:
		memcpy(m_data, data, h*w);
		break;
	case TILE_MODE_4BPP:
		for (int i=0; i<(h*w/2 + ((h*w) % 2));i++){
			m_data[i*2+1] = (data[i]&0xF0)>>4;
			m_data[i*2] = (data[i]&0x0F);
			m_data[i*2] =  (int)(m_data[i*2] * 256) / 16;
			m_data[i*2 +1]= (int)(m_data[i*2+ 1] * 256) /16;
		}
		break;

	}
	return m_data;
}

unsigned char* CTile::getRGBData()
{
	unsigned char* res;
	res=new unsigned char[size*3];

	for(int i=0; i<size; i++)
	{
		CColor* c = m_palette->getColor(m_data[i]);
		c->getColor(res+i*3, COL_MODE_24RGB);
	}
	return res;
}
