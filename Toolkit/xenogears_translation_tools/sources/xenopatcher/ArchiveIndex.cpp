#include "StdAfx.h"
#include ".\archiveindex.h"

CArchiveIndex::CArchiveIndex()
{
	m_List = NULL;
}

CArchiveIndex::~CArchiveIndex()
{
	if (m_List!=NULL) delete[] m_List;
}

int CArchiveIndex::ReadIndex(unsigned char* index, long size)
{
	/**
	 **Inizializza la struttura dati interna dato l'indice dei file
	 **Ritorna 1 se tutto ok, 0 altrimenti
	 **/

	int i=0;
	m_ListLength = size/7;
	m_List = new entry[size/7];
	
	//Lettura dell'indice
	while(i<m_ListLength){
		unsigned long tSector = 0;
		unsigned long tSize = 0;

		memcpy(&tSector, index + i * 7, 3);
		memcpy(&tSize, index + i * 7 + 3, 4);
		memset(&(m_List[i]),0,sizeof(entry));
		m_List[i].sector = tSector;
		m_List[i].size = tSize;
		m_List[i].type = DetectType(tSector, tSize);
		m_List[i].change = 0;
		strcpy(m_List[i].path,"");
		i++;
	}

	//Controllo finale (l'ultimo settore deve essere 0xFFFFFF)
	if (m_List[i-1].sector != 0xFFFFFF)
		return 0;

	return 1;	
}

int CArchiveIndex::WriteIndex(unsigned char *buffer, unsigned long *size)
{
	/**
	 **Ritorna un buffer che contiene l'indice dei file
	 **/
	int i=0;
	unsigned long tSector;
	unsigned long tSize;

	*size=m_ListLength*7;


	//Scrittura dell'indice
	while(i<m_ListLength - 1){
		tSector = m_List[i].sector;
		tSize = m_List[i].size;

		memcpy(buffer + i * 7, &tSector, 3);
		memcpy(buffer + i * 7 + 3, &tSize, 4);
		i++;
	}
	tSector=0xFFFFFF;
	memcpy(buffer + i * 7, &tSector, 3);

	return 1;
}

int CArchiveIndex::DetectType(unsigned long sector, unsigned long size)
{
	/**
	 **Determina se una voce dell'indice punta effettivamente a
	 **un file oppure no.
	 **All'interno dell'indice vi sono infatti voci non valide (tutti 0)
	 **oppure altre che identificano le directory
	 **/
	if((sector != 0) && (size < 0xFF000000) && (size > 0)) return TYPE_FILE;
	else if ((sector == 0) && (size == 0)) return TYPE_ZEROS;
	else return TYPE_OTHER;
}


int CArchiveIndex::UpdateIndex()
{
	/**
	 **Modifica l'indice cambiando le posizioni dei file in relazione
	 **alle loro lunghezze.
	 **Usare questa funzione quando si cambia la dimensione di un file
	 **per rendinere di nuovo consistente l'indice
	 **Nota: I primi 18 file (STR) non vengono modificati perché usano
	 **più di 2048 byte per settore
	 **/

	int i=0;
	unsigned long pSector = m_List[nFileToSkip].sector;
	for(i=nFileToSkip;i<m_ListLength;i++){
		switch (m_List[i].type)
		{
			case TYPE_FILE:
				m_List[i].sector = pSector;
				pSector+=SizeToSectors(m_List[i].size, 2048);
				break;
			case TYPE_ZEROS:
				break;
			case TYPE_OTHER:
				m_List[i].sector = pSector;
				break;
			default:
				return 0;
		}
	}
	return 1;
}

/**
 **Funzioni generiche per la lettura/scrittura delle varibaili private
 **/
int CArchiveIndex::getIndexLength()
{
	return m_ListLength;
}

unsigned long CArchiveIndex::getSector(int nfile)
{
	if (nfile < m_ListLength) return m_List[nfile].sector;
	else return -1;
}

unsigned long CArchiveIndex::getSize(int nfile)
{
	if (nfile < m_ListLength) return m_List[nfile].size;
	else return -1;
}

int CArchiveIndex::getType(int nfile)
{
	if (nfile < m_ListLength) return m_List[nfile].type;
	else return -1;
}


int CArchiveIndex::getChangedFlag(int nfile)
{
	if (nfile < m_ListLength) return m_List[nfile].change;
	else return -1;
}

char* CArchiveIndex::getNewPath(int nfile, char *path)
{
	if (nfile < m_ListLength){
		strcpy (path, m_List[nfile].path);
		return path;
	}	
	else return NULL;
}

int CArchiveIndex::setNewPath(int nfile, char *path)
{
	//
	//Modifica il campo path del file specificato
	//Aggiorna inoltre il file con la nuova lugnhezza e ricalcola
	//l'indice
	//
	FILE* file;
	if (nfile >= m_ListLength)	
		return 0;
	

	file = fopen(path, "rb");
	if(file != NULL){
		unsigned long tSize = 0;
		strcpy(m_List[nfile].path, path);
		m_List[nfile].change=1;
	
		fseek(file,0,SEEK_END);
		tSize = ftell(file);
		m_List[nfile].size = tSize;
		fclose(file);
		UpdateIndex();
		return 1;
	}
	return 0;
}

unsigned long CArchiveIndex::SizeToSectors(unsigned long size, int secsize)
{
	/**
	 **Converte una lunghezza in numero di settori
	 **/
	unsigned long temp;
	temp=size/secsize;
	if(size%secsize != 0) temp++;
	return temp;
}

int CArchiveIndex::SetFileToSkip(int num)
{
	nFileToSkip = num;
	return num;
}



int CArchiveIndex::setNewFile(int fnum, int offset, int size)
{
	if (fnum >= m_ListLength)	
		return 0;
	m_List[fnum].change = 1;
	m_List[fnum].newOffset = offset;
	m_List[fnum].size = size;
	UpdateIndex();
	return 1;
}

int CArchiveIndex::getNewOffset(int fnum)
{
	if (fnum >= m_ListLength)	
		return -1;

	return m_List[fnum].newOffset;
}
