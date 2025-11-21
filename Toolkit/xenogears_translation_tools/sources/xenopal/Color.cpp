// Color.cpp: implementation of the CColor class.
//
//////////////////////////////////////////////////////////////////////

#include "Color.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColor::CColor(unsigned char* v, int mode)
{
	switch(mode){
	case COL_MODE_24RGB:
		r=v[0];
		g=v[1];
		b=v[2];
		break;
	case COL_MODE_16TBGR:
		b=((v[1]&0x7C)>>2);
		g=((v[1]&0x03)<<3) + ((v[0]&0xE0)>>5);
		r=(v[0]&0x1F);
		b=b*255/31;
		g=g*255/31;
		r=r*255/31;
		break;
	case COL_MODE_24YUV:
		r = (int)(v[0] + (1.4075 * (v[2] - 128)));
		g = (int)(v[0] - (0.3455 * (v[1] - 128) - (0.7169 * (v[2] - 128))));
		b = (int)(v[0] + (1.7790 * (v[1] - 128)));
		break;
	default:
		r=0;
		g=0;
		b=0;
		break;
	}
}

CColor::~CColor()
{

}

unsigned char* CColor::getColor(unsigned char *v, int mode)
{
	switch(mode){
	case COL_MODE_24RGB:
		v[0]=r;
		v[1]=g;
		v[2]=b;
		break;
	case COL_MODE_16TBGR:
		v[0] =(int) (r *  .299 + g *  .587 + b *  .114);
		v[1] =(int) (r * -.169 + g * -.332 + b *  .500 + 128.);
		v[2] =(int) (r *  .500 + g * -.419 + b * -.0813 + 128.);
		break;
	default:
		v[0]=0;
		v[1]=0;
		v[2]=0;
		break;
	}
	return v;
}

double CColor::distance(CColor* c)
{
	unsigned char v1[3], v2[3];
	getColor(v1, COL_MODE_24YUV);
	c->getColor(v2, COL_MODE_24YUV);
	return sqrt((v1[0] - v2[0])*(v1[0] - v2[0])+(v1[1] - v2[1])*(v1[1] - v2[1])+(v1[2] - v2[2])*(v1[2] - v2[2]));
}

int CColor::equals(CColor* c)
{
	return (b==c->b && g==c->g && r==c->r);
}
