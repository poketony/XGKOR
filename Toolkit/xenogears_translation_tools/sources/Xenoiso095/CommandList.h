#pragma once

typedef struct{
	int num;
	char path[100];
}FILE_ENTRY;

class CCommandList  
{
public:
	int m_nCdType;
	char* getDst(char* file);
	char* getSrc(char* file);
	FILE_ENTRY* getNextFile(FILE_ENTRY* file);
	int setList(char* filename);
	CCommandList();
	virtual ~CCommandList();

private:
	FILE* list;
	char curpath[100];
protected:
	int m_bFix;
	int m_inDir;
	char src[100];
	char dst[100];

};
