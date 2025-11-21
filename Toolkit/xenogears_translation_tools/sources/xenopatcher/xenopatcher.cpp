// xenopatcher.cpp : definisce i comportamenti delle classi per l'applicazione.
//

#include "stdafx.h"
#include "xenopatcher.h"
#include "xenopatcherDlg.h"
#include ".\xenopatcher.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CxenopatcherApp

BEGIN_MESSAGE_MAP(CxenopatcherApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_COMMAND(ID_ESCAPE, OnEscape)
END_MESSAGE_MAP()


// costruzione di CxenopatcherApp

CxenopatcherApp::CxenopatcherApp()
{
	// TODO: inserire qui il codice di costruzione.
	// Inserire l'inizializzazione significativa in InitInstance.
}


// L'unico e solo oggetto CxenopatcherApp

CxenopatcherApp theApp;


// Inizializzazione di CxenopatcherApp

BOOL CxenopatcherApp::InitInstance()
{
	// InitCommonControls() è necessario in Windows XP se nel manifesto
	// di un'applicazione è specificato l'utilizzo di ComCtl32.dll versione 6 o successiva per attivare
	// gli stili visuali. In caso contrario, non sarà possibile creare finestre.
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Inizializzazione standard
	// Se non si utilizzano queste funzionalità e si desidera ridurre la dimensione
	// dell'eseguibile finale, rimuovere
	// le routine di inizializzazione specifiche non necessarie
	// Modificare la chiave del Registro di sistema in cui sono memorizzate le impostazioni
	// TODO: modificare questa stringa con informazioni appropriate,
	// ad esempio il nome della propria società
	SetRegistryKey(_T("Applicazioni locali generate tramite la Creazione guidata di applicazioni locali"));

	CxenopatcherDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: inserire qui il codice per gestire la chiusura della finestra di dialogo 
		//  tramite il pulsante OK.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: inserire qui il codice per gestire la chiusura della finestra di dialogo 
		//  tramite il pulsante Annulla.
	}

	// Poiché la finestra di dialogo è stata chiusa, restituisce FALSE in modo che l'applicazione
	//  venga terminata, anziché avviare la message pump dell'applicazione.
	return FALSE;
}

void CxenopatcherApp::OnEscape()
{
	// TODO: aggiungere qui il codice per la gestione dei comandi.
}


