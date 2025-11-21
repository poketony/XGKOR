================================================================================
    LIBRERIA DI CLASSI MFC: xenopatcher Informazioni generali sul progetto
===============================================================================

Questa applicazione xenopatcher è stata creata dalla Creazione guidata applicazioni non solo per illustrare le nozioni fondamentali sull'utilizzo delle classi MFC, ma anche per fornire un punto di inizio per la creazione di un'applicazione.

In questo file è riassunto il contenuto di ciascun file che 
fa parte dell'applicazione xenopatcher.

xenopatcher.vcproj
    File di progetto principale relativo ai progetti VC++ generati utilizzando la Creazione guidata applicazioni. 
    Contiene informazioni sulla versione di Visual C++ che ha generato il file e informazioni sulle piattaforme, le configurazioni e le funzionalità del progetto
    selezionate tramite la Creazione guidata applicazioni.

xenopatcher.h
    File di intestazione principale dell'applicazione. Include altre
    intestazioni specifiche del progetto, (compresa Resource.h) e 
    dichiara la classe dell'applicazione CxenopatcherApp.

xenopatcher.cpp
    File di origine principale dell'applicazione che contiene la
    classe dell'applicazione CxenopatcherApp.

xenopatcher.rc
    Elenco di tutte le risorse Microsoft Windows utilizzate dal
    programma. Include le icone, le bitmap e i cursori memorizzati nella 
    sottodirectory RES. È possibile modificare questo file direttamente in
    Microsoft Visual C++. Le risorse del progetto si trovano in 1040.

res\xenopatcher.ico
    File di icona che viene utilizzato come icona dell'applicazione.
    L'icona è inclusa dal principale file di risorse xenopatcher.rc.

res\xenopatcher.rc2
    File contenente risorse che non sono modificate da Microsoft 
    Visual C++. È necessario inserire in questo file tutte le risorse
    non modificabili dall'editor di risorse.

/////////////////////////////////////////////////////////////////////////////

La Creazione guidata applicazioni crea una classe di finestre di dialogo:
xenopatcherDlg.h, xenopatcherDlg.cpp - Finestra di dialogo
    Questi file contengono la classe CxenopatcherDlg. Questa classe
    definisce il comportamento della finestra principale dell'applicazione
    creata. Il modello della finestra di dialogo si trova nel progetto 
    xenopatcher.rc, che può essere modificato in 
    Microsoft Visual C++.
/////////////////////////////////////////////////////////////////////////////

Altre funzionalità:

Controlli ActiveX
    L'applicazione include il supporto per l'utilizzo dei controlli ActiveX.
/////////////////////////////////////////////////////////////////////////////

Altri file standard:

StdAfx.h, StdAfx.cpp
    Questi file sono utilizzati per creare un file di intestazione 
    precompilato (PCH, precompiled header )denominato xenopatcher.pch 
    e tipi di file precompilati denominati StdAfx.obj.

Resource.h
    File di intestazione standard che definisce nuovi ID di risorse.
    Con Microsoft Visual C++ è possibile leggere e aggiornare questo file.

/////////////////////////////////////////////////////////////////////////////

Altre note:

La Creazione guidata applicazioni utilizza l'istruzione "TODO:" per indicare parti del codice di origine che vanno aggiunte o personalizzate.

Se l'applicazione utilizza classi MFC in una DLL condivisa ed è scritta in una lingua diversa da quella del sistema operativo corrente, sarà necessario copiare le rispettive risorse localizzate MFC70XXX.DLL dalla directory Win\System contenuta nel CD-ROM di Microsoft Visual C++ al sistema del computer o directory system32 e rinominare la DLL in MFCLOC.DLL. ("XXX" sta per l'abbreviazione della lingua. Ad esempio, MFC70DEU.DLL contiene le risorse tradotte in tedesco.) Se non si esegue questa operazione, alcuni elementi di interfaccia dell'applicazione rimarranno nella lingua del sistema operativo.

/////////////////////////////////////////////////////////////////////////////
