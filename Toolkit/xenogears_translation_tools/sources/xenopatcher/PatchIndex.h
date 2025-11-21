#pragma once
#include "afxtempl.h"
#include "PatchData.h"


class CPatchIndex : public CArray<CPatchData,CPatchData&>
{
public:
	CPatchIndex(void);
	~CPatchIndex(void);
protected:
public:
	//Aggiungi un File alla lista dei file da sostituire
	//L'unico parametro passato è il path per gli altri si usano i valori di default
	int AddFile(CString strPathName, int num);

	//Aggiungi tutti i file contenuti in una directory alla lista
	//L'unico parametro passato è il path per gli altri si usano i valori di default
	int AddDir(CString strPath);
	int WriteIndex(unsigned char* buffer);
	int CalcOffset(void);
	int ReadIndex(CString strPath);
	int ReadFile(int i, unsigned char* buffer);
protected:
	CString m_strFileName;
};
