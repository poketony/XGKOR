// xenopatcherDlg.cpp : file di implementazione
//

#include "stdafx.h"
#include "xenopatcher.h"
#include "xenopatcherDlg.h"
#include ".\xenopatcherdlg.h"
#include "archiveindex.h"
#include "isomanager.h"
#include "patchindex.h"
#include "Hyperlink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



typedef struct {
	CString strIso;
	CString strPatch;
	CString strVoice;
	CString strComm;
	int backup;
	int cdType;
	HWND hWnd;
} ThreadParam;

UINT ThreadFunc (LPVOID pParam);
int SizeToSectors(int length, int sec_size);
int FindEndOfIndex(unsigned char* buffer, int maxsize);


// finestra di dialogo CAboutDlg utilizzata per visualizzare le informazioni sull'applicazione.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dati della finestra di dialogo
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // supporto DDX/DDV

// Implementazione
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	CHyperlink m_hl;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// finestra di dialogo CxenopatcherDlg



CxenopatcherDlg::CxenopatcherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CxenopatcherDlg::IDD, pParent)
	, m_strIsoPath(_T(""))
	, m_strPatchPath(_T(""))
	, m_strStatus(_T(""))
	, m_strVoice(_T(""))
	, m_strComm(_T(""))
	, m_bBackup(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hAccel = ::LoadAccelerators (AfxGetInstanceHandle (),MAKEINTRESOURCE (IDR_ACCELL));


}

void CxenopatcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDISO, m_strIsoPath);
	DDX_Text(pDX, IDC_EDPATCH, m_strPatchPath);
	DDX_Text(pDX, IDC_EDSTATUS, m_strStatus);
	DDX_CBString(pDX, IDC_CMBVOICE, m_strVoice);
	DDX_Control(pDX, IDC_PROGRESSBAR, m_wndProgress);
	DDX_CBString(pDX, IDC_CMBCOMM, m_strComm);
	DDX_Check(pDX, IDC_CHBACKUP, m_bBackup);
}

BEGIN_MESSAGE_MAP(CxenopatcherDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BROWSEISO, OnBnClickedBrowseiso)
	ON_BN_CLICKED(IDC_BROWSEPATCH, OnBnClickedBrowsepatch)
	ON_BN_CLICKED(IDC_BTAPPLY, OnBnClickedBtapply)
	ON_COMMAND(ID_RETURN, OnReturn)
	ON_MESSAGE(WM_UPDATEBAR, OnUpdateBar)
	ON_MESSAGE(WM_THREADEND, OnThreadEnd)
	ON_COMMAND(ID__INFORMAZIONISUXENOPATCHER, OnAbout)
	ON_COMMAND(ID_FILE_ESCI, OnFileEsci)
	ON_WM_HELPINFO()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// gestori di messaggi di CxenopatcherDlg

BOOL CxenopatcherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Aggiungere la voce di menu "Informazioni su..." al menu di sistema.

	// IDM_ABOUTBOX deve trovarsi tra i comandi di sistema.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Impostare l'icona per questa finestra di dialogo. Il framework non esegue questa operazione automaticamente
	//  se la finestra principale dell'applicazione non è una finestra di dialogo.
	SetIcon(m_hIcon, TRUE);			// Impostare icona grande.
	SetIcon(m_hIcon, FALSE);		// Impostare icona piccola.

	// TODO: aggiungere qui inizializzazione aggiuntiva.

	CComboBox cmbBox;
	cmbBox.Attach(GetDlgItem(IDC_CMBVOICE)->m_hWnd);
	cmbBox.SetWindowPos(NULL, 0, 0, 100, 100, SWP_NOZORDER|SWP_NOMOVE);
	cmbBox.Detach();
	cmbBox.Attach(GetDlgItem(IDC_CMBCOMM)->m_hWnd);
	cmbBox.SetWindowPos(NULL, 0, 0, 100, 100, SWP_NOZORDER|SWP_NOMOVE);
	cmbBox.Detach();

	CStatic st;
	st.Attach(GetDlgItem(IDC_STDISC)->m_hWnd);
	CFont fnt;
	fnt.CreatePointFont(12,"Arial");
	st.SetFont(&fnt);
	st.Detach();

	m_bRedBrush.CreateSolidBrush (RGB (245, 19, 20));

	m_wndProgress.SetRange(0,1000);
	m_strComm="Giapponesi";
	m_strVoice="Giapponesi";
	m_strStatus = "Pronto";
	UpdateData(0);

	return TRUE;  // restituisce TRUE a meno che non venga impostato lo stato attivo su un controllo.
}

void CxenopatcherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Se si aggiunge alla finestra di dialogo un pulsante di riduzione a icona, per trascinare l'icona sarà necessario
//  il codice sottostante. Per le applicazioni MFC che utilizzano il modello documento/vista,
//  questa operazione viene eseguita automaticamente dal framework.

void CxenopatcherDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contesto di periferica per il disegno

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrare l'icona nel rettangolo client.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Disegnare l'icona
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Il sistema chiama questa funzione per ottenere la visualizzazione del cursore durante il trascinamento
//  della finestra ridotta a icona.
HCURSOR CxenopatcherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CxenopatcherDlg::OnBnClickedBrowseiso()
{
	static char szFilter[] = "File Immagine (*.bin;*.img)|*.bin; *.img|Tutti i File (*.*)|*.*||";
	CFileDialog dlg(TRUE,0,0,OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,szFilter);

	if (dlg.DoModal()==IDOK){
		m_strIsoPath = dlg.GetPathName();
		UpdateData(0);
	}
}

void CxenopatcherDlg::OnBnClickedBrowsepatch()
{
	static char szFilter[] = "Xenogears Patch (*.xpt)|*.xpt|Tutti i File (*.*)|*.*||";
	CFileDialog dlg(TRUE,0,0,OFN_HIDEREADONLY|OFN_FILEMUSTEXIST,szFilter);
	
	if (dlg.DoModal()==IDOK){
		m_strPatchPath = dlg.GetPathName();
		UpdateData(0);
	}
}


void CxenopatcherDlg::OnBnClickedBtapply()
{
	UpdateData(1);
	CIsoManager src;

	//Controllo dei file
	if ((m_strPatchPath == "")||(m_strIsoPath == "")){
		AfxMessageBox("Iso o patch non selezionata");
		return;
	}

	//Warning sulla traduzione dei video
//	if (m_strVoice == "Giapponesi")
//		MessageBox("ATTENZIONE!\r\nQuesta patch NON TRADUCE i filmati!\r\nPer giocare con i video in lingua originale e sottotitolati\r\noccorre applicare l'apposita patch scaricabile da www.sadnescity.it","Attenzione");

	if (!src.OpenIso(m_strIsoPath)){
		AfxMessageBox("Impossibile aprire il file iso!");
		return;
	}
	unsigned char realtoc[2352];
	src.Read(realtoc,22,1);
	

	ThreadParam tp;
	tp.strPatch = m_strPatchPath;
	tp.strIso = m_strIsoPath;
	tp.strVoice = m_strVoice;
	tp.strComm = m_strComm;
	tp.cdType = DetectCD(realtoc);
	tp.backup = m_bBackup;
	tp.hWnd = this->m_hWnd;
	CWinThread* pThread = AfxBeginThread(ThreadFunc, &tp);
	CString strTemp;
	strTemp.Format("Applicazione patch in corso al cd%d...",tp.cdType);
	m_strStatus = strTemp;
	UpdateData(0);
	//ApplyPatch();
}

int CxenopatcherDlg::ModifyName(CString* strPath)
{

	return 0;
}

int CxenopatcherDlg::DetectCD(unsigned char* index)
{
	char name[15];
	memset(name, 0, 15);
	memcpy(name,index + 129,11);
	if (strcmp(name, "SLUS_006.64")==0)
		return 1;
	else if (strcmp(name, "SLUS_006.69")==0)
		return 2;
	return 0;
}

int FindEndOfIndex(unsigned char* buffer, int maxsize)
{
	long i=0;
	while(i < maxsize){
		if ((buffer[i] == 0xFF) && (buffer[i+1]==0xFF) && (buffer[i+2]==0xFF))
			return i+7;
		i+=7;
	}
	return 0;
}

int SizeToSectors(int length, int sec_size)
{
	unsigned long temp;
	temp=length/sec_size;
	if(length%sec_size != 0) temp++;
	return temp;
}



int CxenopatcherDlg::ApplyPatch(void)
{
/*	EnableWindow(0);
	UpdateData(1);
	m_strStatus = "Apertura Iso...";
	UpdateData(0);
	CIsoManager src, dst;
	if (!src.OpenIso(m_strIsoPath)){
		AfxMessageBox("Impossibile aprire il file iso!");
		EnableWindow(1);
		return 0;
	}
	m_strStatus += "Fatto!\r\n";
	UpdateData(0);
	dst.CreateIso("temp.dat");
	unsigned char indice[32768];
	memset(indice,0,32768);
	src.Read(indice, 24, 16);
	int VideoFiles, FirstNonVideoSector, IndexSector2, subval;
	m_strStatus += "Rilevamento CD...";
	UpdateData(0);
	unsigned char realtoc[2352];
	src.Read(realtoc,22,1);
	unsigned char chCD=0, chVoice = 0;
	switch(DetectCD(realtoc)){
		case 1:
			VideoFiles = 18;
			FirstNonVideoSector = 108561;
			IndexSector2 = 108607;
			chCD = CD1;
			subval=0;
			break;
		case 2:
			VideoFiles = 14;
			FirstNonVideoSector = 172873;
			IndexSector2 = 172919;
			chCD = CD2;
			subval=5;
			break;
		default:
			AfxMessageBox("Tipo CD Sconosciuto!");
			EnableWindow(1);
			return 0;
			break;
	}
	if (m_strVoice == "Giapponese")
		chVoice = VOICEJAP;
	else if (m_strVoice == "Inglese")
		chVoice = VOICEENG;
	m_strStatus += "Fatto!\r\n";
	UpdateData(0);
	
	CArchiveIndex indexs, indexd;
	indexs.SetFileToSkip(VideoFiles);
	indexd.SetFileToSkip(VideoFiles);
	m_strStatus += "Lettura Indice...";
	UpdateData(0);
	unsigned long indexsize=FindEndOfIndex(indice, 32768);
	if (!indexs.ReadIndex(indice,indexsize)){
		AfxMessageBox("Errore nella lettura dell'indice!");
		EnableWindow(1);
		return 0;
	}
	if (!indexd.ReadIndex(indice,indexsize)){
		printf("Errore nella lettura dell'indice\r\n");
		AfxMessageBox("Errore nella lettura dell'indice!");
		EnableWindow(1);
		return 0;
	}
	m_strStatus += "Fatto!\r\n";
	UpdateData(0);

	m_strStatus += "Apertura Patch...";
	UpdateData(0);
	CPatchIndex patch;
	patch.ReadIndex(m_strPatchPath);
	m_strStatus += "Fatto!\r\n";
	UpdateData(0);

	m_strStatus += "Aggiornamento Indice...";
	UpdateData(0);
	for (int i=0; i<patch.GetCount(); i++){
		if((patch[i].getFormat() & chCD)&&(patch[i].getFormat() & chVoice))
			indexd.setNewFile(patch[i].getFileNum() - subval, patch[i].getOffset(), patch[i].getSize());
	}
	m_strStatus += "Fatto!\r\n";
	UpdateData(0);

	m_strStatus += "Copia dei filmati...";
	UpdateData(0);
	unsigned char tbuffer[32*2352];
	for (i=0; i<FirstNonVideoSector-32; i+=32)
	{
		src.ReadRawSectors(tbuffer, i, 32);
		dst.AppendRawSectors(tbuffer, 32);
	}
	src.ReadRawSectors(tbuffer, i, FirstNonVideoSector-i);
	dst.AppendRawSectors(tbuffer, FirstNonVideoSector-i);
	m_strStatus += "Fatto!\r\n";
	UpdateData(0);

	indexsize = indexs.getIndexLength();
	for (i=VideoFiles; (unsigned)i <indexsize; i++){
		CString strTemp;
		strTemp.Format("Scrittura file %d...", i);
		m_strStatus += strTemp;
		UpdateData(0);

		if (indexd.getType(i)==TYPE_FILE){
			if (!indexd.getChangedFlag(i)){
				//file non modificato => copialo dall'indice non modificato
				int length = indexs.getSize(i);	
				int len_sec = SizeToSectors(length,2048);
				for (int cc=0; cc<len_sec-32; cc+=32){
					src.Read(tbuffer, indexs.getSector(i) + cc, 32);///!!!
					dst.Append(tbuffer, 32);
				}
				src.Read(tbuffer, indexs.getSector(i) + cc, len_sec-cc);
				dst.Append(tbuffer, len_sec-cc);
			}
			else{
				//file modificato
				int length = indexd.getSize(i);
				int len_sec = SizeToSectors(length,2048);
				unsigned char* filedata;
				filedata = new unsigned char[length];
				CFile fp;
				fp.Open(m_strPatchPath, CFile::modeRead);
				fp.Seek(indexd.getNewOffset(i), CFile::begin);
				for (int cc=0; cc<len_sec-32; cc+=32){
					fp.Read(tbuffer,2048*32);
					dst.Append(tbuffer, 32);
				}
				fp.Read(tbuffer,length-(cc*2048));
				dst.Append(tbuffer, (len_sec-cc));
				fp.Close();
			}
			
		}
		m_strStatus += "Fatto!\r\n";
		UpdateData(0);
	}


	//Scrivi Indice
	m_strStatus += "Scrittura indice...";
	UpdateData(0);
	memset(indice,0,32768);
	indexd.WriteIndex(indice, &indexsize);
	dst.Write(indice,24,16);
	memset(indice,0xFF,4);
	indexd.WriteIndex(indice+4, &indexsize);
	dst.Write(indice,IndexSector2,16);
	m_strStatus += "Fatto!\r\n";
	UpdateData(0);
	
	CString strBackup = m_strIsoPath + "BACKUP";
	rename(m_strIsoPath, strBackup);
	rename("temp.dat", m_strIsoPath);
	EnableWindow(1);
*/	return -1;

}

UINT ThreadFunc (LPVOID pParam)
{
	CString strIsoPath = ((ThreadParam*)pParam)->strIso;
	CString strPatchPath = ((ThreadParam*)pParam)->strPatch;
	CString strVoice = ((ThreadParam*)pParam)->strVoice;
	CString strComm = ((ThreadParam*)pParam)->strComm;
	int cdType = ((ThreadParam*)pParam)->cdType;
	int backup = ((ThreadParam*)pParam)->backup;
	HWND hWnd = ((ThreadParam*)pParam)->hWnd;
	CIsoManager src, dst;
	if (!src.OpenIso(strIsoPath)){
		AfxMessageBox("Impossibile aprire il file iso!");
		return 0;
	}
	dst.CreateIso("temp.dat");
	unsigned char indice[32768];
	memset(indice,0,32768);
	src.Read(indice, 24, 16);
	int VideoFiles, FirstNonVideoSector, IndexSector2, subval;
	unsigned char realtoc[2352];
	src.Read(realtoc,22,1);
	unsigned char chCD=0, chVoice = 0, chComm = 0;
	switch(cdType){
		case 1:
			VideoFiles = 18;
			FirstNonVideoSector = 108561;
			IndexSector2 = 108607;
			chCD = CD1;
			subval=0;
			break;
		case 2:
			VideoFiles = 14;
			FirstNonVideoSector = 172873;
			IndexSector2 = 172919;
			chCD = CD2;
			subval=5;
			break;
		default:
			AfxMessageBox("Tipo CD Sconosciuto!");
			return 0;
			break;
	}
	if (strVoice == "Giapponesi")
		chVoice = VOICEJAP;
	else if (strVoice == "Americane")
		chVoice = VOICEENG;
	if (strComm == "Americani")
		chComm = COMM_A;
	else if (strComm == "Giapponesi")
		chComm = COMM_J;
	
	CArchiveIndex indexs, indexd;
	indexs.SetFileToSkip(VideoFiles);
	indexd.SetFileToSkip(VideoFiles);
	unsigned long indexsize=FindEndOfIndex(indice, 32768);
	if (!indexs.ReadIndex(indice,indexsize)){
		AfxMessageBox("Errore nella lettura dell'indice!");
		return 0;
	}
	if (!indexd.ReadIndex(indice,indexsize)){
		printf("Errore nella lettura dell'indice\r\n");
		AfxMessageBox("Errore nella lettura dell'indice!");
		return 0;
	}

	CPatchIndex patch;
	patch.ReadIndex(strPatchPath);
	


	for (int i=0; i<patch.GetCount(); i++){
		if((patch[i].getFormat() & chCD)&&(patch[i].getFormat() & chVoice)&&(patch[i].getFormat() & chComm))
			indexd.setNewFile(patch[i].getFileNum() - subval, patch[i].getOffset(), patch[i].getSize());
	}

	unsigned char tbuffer[32*2352];
	for (i=0; i<FirstNonVideoSector-32; i+=32)
	{
		src.ReadRawSectors(tbuffer, i, 32);
		dst.AppendRawSectors(tbuffer, 32);
		::PostMessage (hWnd, WM_UPDATEBAR, dst.getNumOfSectors(), 305586);
	}
	src.ReadRawSectors(tbuffer, i, FirstNonVideoSector-i);
	dst.AppendRawSectors(tbuffer, FirstNonVideoSector-i);

	indexsize = indexs.getIndexLength();
	for (i=VideoFiles; (unsigned)i <indexsize; i++){
		::PostMessage (hWnd, WM_UPDATEBAR, dst.getNumOfSectors(), 305586);
		if (indexd.getType(i)==TYPE_FILE){
			if (!indexd.getChangedFlag(i)){
				//file non modificato => copialo dall'indice non modificato
				int length = indexs.getSize(i);	
				int len_sec = SizeToSectors(length,2048);
				for (int cc=0; cc<len_sec-32; cc+=32){
					src.Read(tbuffer, indexs.getSector(i) + cc, 32);///!!!
					dst.Append(tbuffer, 32);
				}
				src.Read(tbuffer, indexs.getSector(i) + cc, len_sec-cc);
				dst.Append(tbuffer, len_sec-cc,1);
			}
			else{
				//file modificato
				int length = indexd.getSize(i);
				int len_sec = SizeToSectors(length,2048);
				unsigned char* filedata;
				filedata = new unsigned char[length];
				CFile fp;
				fp.Open(strPatchPath, CFile::modeRead);
				fp.Seek(indexd.getNewOffset(i), CFile::begin);
				for (int cc=0; cc<len_sec-32; cc+=32){
					fp.Read(tbuffer,2048*32);
					dst.Append(tbuffer, 32);
				}
				fp.Read(tbuffer,length-(cc*2048));
				dst.Append(tbuffer, (len_sec-cc),1);
				fp.Close();
			}
			
		}
	}


	//Scrivi Indice
	memset(indice,0,32768);
	indexd.WriteIndex(indice, &indexsize);
	dst.Write(indice,24,16,1);
	memset(indice,0xFF,4);
	indexd.WriteIndex(indice+4, &indexsize);
	dst.Write(indice,IndexSector2,16);

	//CFile ftemp;
	//ftemp.Open("indice.dat", CFile::modeCreate | CFile::modeReadWrite);
	//ftemp.Write(indice,32768);
	//ftemp.Close();
	if (backup){
		CString strBackup = strIsoPath + "BACKUP";
		rename(strIsoPath, strBackup);
		rename("temp.dat", strIsoPath);
	}
	else{
		remove(strIsoPath);
		rename("temp.dat", strIsoPath);
	}
	::PostMessage (hWnd, WM_THREADEND, dst.getNumOfSectors(), 305586);
	return -1;
}

 

void CxenopatcherDlg::OnReturn()
{
	// TODO: aggiungere qui il codice per la gestione dei comandi.
}

long CxenopatcherDlg::OnUpdateBar(WPARAM wParam, LPARAM lParam)
{
	m_wndProgress.SetPos((int)wParam*1000/(int)lParam);
	return 0;
}

long CxenopatcherDlg::OnThreadEnd(WPARAM wParam, LPARAM lParam)
{
	m_strStatus = "Patch applicata";
	UpdateData(0);
	return 0;
}

BOOL CxenopatcherDlg::PreTranslateMessage(MSG* pMsg)
{
    if (m_hAccel != NULL)
        if (::TranslateAccelerator (m_hWnd, m_hAccel, pMsg))
            return TRUE;
    
    return CDialog::PreTranslateMessage (pMsg);
}

void CxenopatcherDlg::OnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CxenopatcherDlg::OnFileEsci()
{
	::PostMessage(this->m_hWnd, WM_CLOSE,0,0);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    CRect   rctWindow(0, 0, 100, 20);

    m_hl.Create(NULL,"www.sadnescity.it",WS_CHILD, rctWindow, this, 9999);
	m_hl.SetLinkTarget("http:////www.sadnescity.it//");
	m_hl.AllowModsToFont(1);
	m_hl.SetFontName("Arial");
	m_hl.SetFontSize(14);
	m_hl.SetTextColour(RGB(0,0,255));
	m_hl.MoveWindow(120,280,100,20);
	m_hl.ShowWindow(SW_SHOWNORMAL);

	return TRUE;  // return TRUE unless you set the focus to a control
}

BOOL CxenopatcherDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
 // This method does all the work	
 ShowContextHelp(CWnd::FromHandle((HWND)pHelpInfo->hItemHandle),
  pHelpInfo->MousePos, pHelpInfo->iCtrlId);

 // We will proceed the message, so skip the base class
 // return CDialog::OnHelpInfo(pHelpInfo);
 return TRUE;
}

void CxenopatcherDlg::ShowContextHelp(CWnd* pWnd, POINT pt, int iCtrlID)
{
CString s;

 // Load help text from String Table
 if(s.LoadString(iCtrlID))
 {
  HH_POPUP hPop; // HTML Help popup structure

  // Initialize structure to NULLs	
  memset(&hPop, 0, sizeof(hPop));

  // Set size of structure
  hPop.cbStruct         = sizeof(hPop);

  // Yellow background color
  hPop.clrBackground    = RGB(255, 255, 208);

  hPop.clrForeground    = -1; // Font color	
  hPop.rcMargins.left   = -1;
  hPop.rcMargins.bottom = -1;
  hPop.rcMargins.right  = -1;
  hPop.pt               = pt;
  hPop.pszText          = s; // Message from String Table
  hPop.pszFont          = NULL; // Font

  HtmlHelp((DWORD)&hPop, HH_DISPLAY_TEXT_POPUP);
 } // End if found a help string for this request
} // End ShowContextHelp(...)


HBRUSH CxenopatcherDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	CStatic st;
	st.Attach(GetDlgItem(IDC_STDISC)->m_hWnd);
	if (st.m_hWnd == pWnd->m_hWnd){
        pDC->SetTextColor (RGB (255, 255, 255));
        pDC->SetBkColor (RGB (245, 19, 20));
		st.Detach();
		return m_bRedBrush;
	}
	st.Detach();
	return CDialog::OnCtlColor (pDC, pWnd, nCtlColor);

}
