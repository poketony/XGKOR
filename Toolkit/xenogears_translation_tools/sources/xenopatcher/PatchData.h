#pragma once

#define	VOICEJAP	0x01
#define VOICEENG	0x02
#define CD1			0x04
#define CD2			0x08
#define COMM_A		0x10
#define COMM_J		0x20

class CPatchData
{
public:
	CPatchData(void);
	~CPatchData(void);
protected:
	unsigned int m_nFileNum;
	CString m_strPath;
	unsigned int m_nSize;
	unsigned int m_nOffset;
	unsigned char m_chFormat;
public:
	int setFileNum(int nFileNum);
	int setPath(CString strPath);
	int setSize(int nSize);
	int setOffset(int nOffset);
	int setFormat(unsigned char chFormat);
	int setCD(unsigned char chFormat);
	int getFileNum();
	CString getPath();
	int getSize();
	int getOffset();
	unsigned char getFormat();
	int WriteData(unsigned char* buffer);
};
