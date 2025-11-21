#include "StdAfx.h"
#include ".\patchindex.h"

CPatchIndex::CPatchIndex(void)
: m_strFileName(_T(""))
{
	SetSize(0,700);
}

CPatchIndex::~CPatchIndex(void)
{
}


int CPatchIndex::AddFile(CString strPathName, int num)
{
	CFile file;
	if (!file.Open(strPathName, CFile::modeRead))
		return 0;
	int nFileLen = (int)file.GetLength();
	file.Close();

	CPatchData data;
	data.setPath(strPathName);
	data.setFileNum(num);
	data.setSize(nFileLen);
	data.setFormat(VOICEJAP|VOICEENG|CD1|CD2);

	Add(data);
	return -1;
}

int CPatchIndex::AddDir(CString strPath)
{
	CString strFind = strPath+ "\\*.*";
	CString strFile;
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(strFind, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
    do {
		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
		else{
			CFile file;
			strFile = strPath +"\\"+fd.cFileName;
			if (!file.Open(strFile, CFile::modeRead)){
			    FindClose (hFind);
				return 0;
			}
			int nFileLen = (int)file.GetLength();
			file.Close();
	
			CPatchData data;
			data.setPath(strFile);
			data.setFileNum(atoi(fd.cFileName));
			data.setSize(nFileLen);
			data.setFormat(VOICEJAP|VOICEENG|CD1|CD2);

			Add(data);
			}
		} while (FindNextFile (hFind, &fd));
	FindClose (hFind);
	}

	return -1;
}


int CPatchIndex::WriteIndex(unsigned char* buffer)
{
	unsigned char data[16];
	int num = GetCount();
	memset(buffer,0,16);
	memcpy(buffer,&num,4);
	buffer[4]=0x01;	//Versione
	for (int i=0; i<num;i++){
		GetAt(i).WriteData(data);
		memcpy(buffer+(i+1)*16,data,16);
	}
	return -1;
}

int CPatchIndex::CalcOffset(void)
{
	GetAt(0).setOffset((GetCount()+1)*16);
	for (int i=1; i<GetCount();i++){
		GetAt(i).setOffset(GetAt(i-1).getOffset()+GetAt(i-1).getSize());
	}
	return -1;

}

int CPatchIndex::ReadIndex(CString strPath)
{
	CFile file;
	if(!file.Open(strPath,CFile::modeRead))
		return 0;
	m_strFileName = strPath;
	int nNum;
	file.Read(&nNum,4);
	unsigned char* buffer;
	buffer = new unsigned char[nNum*16];
	file.Seek(16,CFile::begin);
	file.Read(buffer,16*nNum);
	file.Close();
	RemoveAll();
	SetSize(0,nNum);
	for (int i=0;i<nNum;i++){
		int temp=0;
		CPatchData data;

		memcpy(&temp,buffer+16*i,2);
		data.setFileNum(temp);
		memcpy(&temp,buffer+16*i+2,4);
		data.setOffset(temp);
		memcpy(&temp,buffer+16*i+6,4);
		data.setSize(temp);
		temp=0;
		memcpy(&temp,buffer+16*i+10,1);
		data.setFormat(temp);
		data.setPath("local");
		Add(data);
	}
	return -1;
}

int CPatchIndex::ReadFile(int i, unsigned char* buffer)
{
	CPatchData data;
	data = GetAt(i);
	buffer = new unsigned char[data.getSize()];
	
	CFile file;
	if(!file.Open(m_strFileName, CFile::modeRead))
		return 0;
	file.Seek(data.getOffset(),CFile::begin);
	file.Read(buffer,data.getSize());
	file.Close();
	return -1;
}
