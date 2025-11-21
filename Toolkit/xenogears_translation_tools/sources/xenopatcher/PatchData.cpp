#include "StdAfx.h"
#include ".\patchdata.h"

CPatchData::CPatchData(void)
{
}

CPatchData::~CPatchData(void)
{
}

int CPatchData::setFileNum(int nFileNum)
{
	m_nFileNum = nFileNum;
	return nFileNum;
}

int CPatchData::setSize(int nSize)
{
	m_nSize = nSize;
	return nSize;
}

int CPatchData::setOffset(int nOffset)
{
	m_nOffset = nOffset;
	return nOffset;
}
int CPatchData::setPath(CString strPath)
{
	m_strPath = strPath;
	return 0;
}

int CPatchData::setFormat(unsigned char chFormat)
{
	m_chFormat = chFormat;
	return 0;
}

int CPatchData::setCD(unsigned char chFormat)
{
	m_chFormat = chFormat;
	return 0;
}

int CPatchData::getFileNum()
{
	return m_nFileNum;
}

int CPatchData::getSize()
{
	return m_nSize;
}

int CPatchData::getOffset()
{
	return m_nOffset;
}

CString CPatchData::getPath()
{
	return m_strPath;
}

unsigned char CPatchData::getFormat()
{
	return m_chFormat;
}

int CPatchData::WriteData(unsigned char* buffer)
{
	memset(buffer,0,16);
	memcpy(buffer,&m_nFileNum,2);
	memcpy(buffer+2,&m_nOffset,4);
	memcpy(buffer+6,&m_nSize,4);
	memcpy(buffer+10,&m_chFormat,1);
	return -1;
}
