// CommandList.cpp: implementation of the CCommandList class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "windows.h"
#include ".\commandlist.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

WIN32_FIND_DATA fd;
HANDLE hFind;

CCommandList::CCommandList()
{
	list = NULL;
	m_inDir = 0;
	m_nCdType = -1;
	m_bFix = 0;
}

CCommandList::~CCommandList()
{
	if (list!=NULL)
		fclose(list);
}

int CCommandList::setList(char* filename)
{
	list = fopen(filename,"rt");
	if (list==NULL)	return 0;


	char cdnum[5];
	fscanf(list,"%s", cdnum);
	fscanf(list, "%s", src);
	fscanf(list, "%s", dst);
	if (strcmp(cdnum, "cd1") == 0) m_nCdType = 1;
	else if (strcmp(cdnum, "cd2") == 0) m_nCdType = 2;
	else if (strcmp(cdnum, "cd2fix") == 0) {m_nCdType = 2; m_bFix=1;}
	
	return m_nCdType;


}

FILE_ENTRY* CCommandList::getNextFile(FILE_ENTRY* file)
{
	int num = 0; char path[100]; char search[100];
	
	if (feof(list) && !m_inDir)	//se sono alla fine del file 
		return NULL;

	if (!m_inDir){
		//Non sono in una sottodirectory
		fscanf(list, "%d,%s",&num,path);	//leggi entry
		if (num == -1){
			//directory
			strcpy(curpath, path);
			strcpy(search, path);
			strcat(search, "\\*.*");
			hFind = ::FindFirstFile (search, &fd);
			if (hFind != INVALID_HANDLE_VALUE){
				do{
					if (fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY){
						strcpy (file->path, path);
						strcat (file->path,"\\");
						strcat (file->path, fd.cFileName);
						file->num=atoi(fd.cFileName);
						if ((m_nCdType == 2)&&(m_bFix == 1)) (file->num) -= 5;
						if (::FindNextFile(hFind, &fd)) m_inDir = TRUE;
						else{m_inDir = FALSE; ::FindClose(hFind);}
						return file;
					}
				}while(::FindNextFile(hFind, &fd));
			}

		}
		else{
			//file
			file->num = num;
			if ((m_nCdType == 2)&&(m_bFix == 1)) (file->num) -= 5;
			strcpy(file->path, path);
			return file;
		}

	}
	else{
		//Sono ancora in una sottodirectory
		strcpy(file->path, curpath);
		strcat (file->path,"\\");
		strcat (file->path, fd.cFileName);
		file->num=atoi(fd.cFileName);
		if ((m_nCdType == 2)&&(m_bFix == 1))(file->num) -= 5;
		if (::FindNextFile(hFind, &fd)) m_inDir = TRUE;
		else{m_inDir = FALSE; ::FindClose(hFind);}
	}
	return file;

}

char* CCommandList::getSrc(char *file)
{
	strcpy(file, src);
	return src;
}

char* CCommandList::getDst(char *file)
{
	strcpy(file, dst);
	return dst;

}
