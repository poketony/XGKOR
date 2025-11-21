// xenopatcher.h : file di intestazione principale per l'applicazione PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error: inclusione di "stdafx.h" prima dell'inclusione di questo file per PCH
#endif

#include "resource.h"		// simboli principali


// CxenopatcherApp:
// Per l'implementazione di questa classe, vedere xenopatcher.cpp.
//

class CxenopatcherApp : public CWinApp
{
public:
	CxenopatcherApp();

// Sostituzioni
	public:
	virtual BOOL InitInstance();

// Implementazione

	DECLARE_MESSAGE_MAP()
	afx_msg void OnEscape();
};

extern CxenopatcherApp theApp;
