// XenoInsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XenoIns.h"
#include "XenoInsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXenoInsDlg dialog

CXenoInsDlg::CXenoInsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXenoInsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXenoInsDlg)
	m_bFix = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXenoInsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXenoInsDlg)
	DDX_Check(pDX, IDC_FIXCD2, m_bFix);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXenoInsDlg, CDialog)
	//{{AFX_MSG_MAP(CXenoInsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ISO_BROWSE, OnIsoBrowse)
	ON_BN_CLICKED(IDC_FILE_BROWSE, OnFileBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXenoInsDlg message handlers

BOOL CXenoInsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXenoInsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXenoInsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXenoInsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CXenoInsDlg::ReadSector(CFile* file, BYTE *pBuffer, DWORD dwStart, UINT nNumOfSectors)
{
	//
	//Legge nNumOfSectors Settori a partire da dwStart e li mette in pBuffer
	//
	
	BYTE bySector[2048];
	UINT i=0;

	for (i=0; i<nNumOfSectors; i++){
		file->Seek((dwStart + i) * 2352 + 24,CFile::begin);
		file->Read(bySector, 2048);
		memcpy(pBuffer + i * 2048, bySector, 2048);
	}
	return TRUE;
}

BOOL CXenoInsDlg::WriteSector(CFile *file, BYTE *pBuffer, DWORD dwStart, UINT nNumOfSectors)
{
	file->Seek(dwStart * 2352 + 24, CFile::begin);

	for (UINT i = 0; i< nNumOfSectors; i++){
		file->Write(pBuffer + (i * 2048), 2048);
		file->Seek(304, CFile::current);
	}
	return TRUE;
}

BOOL CXenoInsDlg::ReadVirtualTOC(CFile* file)
{
	BYTE pBuffer[2048 * 16];
	UINT count;
	BYTE entry[7];
	TOCEntry FInfo;


	ReadSector(file, pBuffer, 24 , 16);


	for (count = 0; count < 2048 * 16 / 7 ; count++){
		memcpy(entry, pBuffer + 7 * count, 7);
		

		//Aggiungi all'array
		FInfo.dwStartSector = entry[0] | (entry[1] << 8) | (entry[2] << 16);
		FInfo.nLength =  entry[3] | (entry[4] << 8) | (entry[5] << 16) | (entry[6] << 24);
		if (FInfo.dwStartSector == 0xffffff)
			break;
		//if (((FInfo.nLength == 0) && (FInfo.dwStartSector > 0)) || (FInfo.nLength > 0xff000000))
		//	continue;
		//if ((FInfo.dwStartSector != 0) && (FInfo.nLength < 0xff000000) && (FInfo.nLength > 0))
		arTOC.Add(FInfo);
	}
	
	return TRUE;
}

void CXenoInsDlg::OnOK() 
{
	CString strIso;
	CString strFile;
	UINT nPos;
	CEdit ed;

	ed.Attach(GetDlgItem(IDC_ED_POS)->m_hWnd);
	ed.GetWindowText(strIso);
	nPos = atoi(strIso);
	if (m_bFix) nPos-=5;
	ed.Detach();
	ed.Attach(GetDlgItem(IDC_ED_FILE)->m_hWnd);
	ed.GetWindowText(strFile);
	ed.Detach();
	ed.Attach(GetDlgItem(IDC_ED_ISO)->m_hWnd);
	ed.GetWindowText(strIso);
	ed.Detach();
	


	CFile iso;
	CFile file;
	CFileException e;
	
	
	//Apre e controlla la iso
	try{
		if(!iso.Open(strIso, CFile::modeReadWrite, &e)){
				AfxMessageBox("Unable to open iso file!");
				return;
		}
	}
	catch(CFileException* e){
		throw e;
	}
	
	//Legge il toc
	ReadVirtualTOC(&iso);
	if (!file.Open(strFile, CFile::modeRead)){
			AfxMessageBox("Unable to open file!");
			return;
	}

	if (nPos<0){
		AfxMessageBox("Position error");
		return;
	}
	DWORD dwTEmp = file.GetLength();
	UINT nTemp = arTOC[nPos].nLength;
	
	if ((file.GetLength() / 2048) != (arTOC[nPos].nLength / 2048)){
		MessageBox ("Uncompatible Length");
	}
	else{
		WriteFile(&iso, &file, nPos);
		MessageBox ("Scrittura eseguita con successo");
	}
	

	file.Close();
	iso.Close();

}

BOOL CXenoInsDlg::WriteFile(CFile *iso, CFile *file, UINT nPosition)
{
	BYTE pBuffer[2048 * 16];
	UINT nNum = 0;
	//Scrivi l'indice 
	ReadSector(iso, pBuffer, 24 , 16);
	DWORD dwFileLength = file->GetLength();
	memcpy(pBuffer + (7 * nPosition) + 3, &dwFileLength, 4);
	WriteSector(iso, pBuffer, 24, 16);

	//Scrivi l'indice nell'exe
	ReadSector(iso, pBuffer, 108607 , 16);
	memcpy(pBuffer + 4 + (7 * nPosition) + 3, &dwFileLength, 4);
	WriteSector(iso, pBuffer, 108607, 16);



	//Scrivi il file
	BYTE FileBuff[32 * 2048];
	UINT i = 0;
	DWORD LastOff = 0;

	while(file->GetPosition() + 32 * 2048 < dwFileLength){
		memset(FileBuff, 0, 32 * 2048);
		file->Read(FileBuff, 32 * 2048);
		WriteSector(iso, FileBuff, arTOC[nPosition].dwStartSector + i * 32, 32);
		i++;
	}
	LastOff = file->GetPosition(); 

	if (LastOff < dwFileLength){
		//Scrivi l'ultimo pezzo di file
		memset(FileBuff, 0, 32 * 2048);
		file->Read(FileBuff, dwFileLength - LastOff);

		UINT nRemSect = (dwFileLength - LastOff) / 2048;
		if ((dwFileLength - LastOff) % 2048 != 0)
			nRemSect++;
		WriteSector(iso, FileBuff, arTOC[nPosition].dwStartSector + i * 32, nRemSect);
	}
	
	return TRUE;
}

void CXenoInsDlg::OnIsoBrowse() 
{
	CFileDialog dlg(TRUE);
	dlg.DoModal();

	CEdit ed;
	ed.Attach(GetDlgItem(IDC_ED_ISO)->m_hWnd);
	ed.SetWindowText(dlg.GetPathName());
	ed.Detach();
	
}

void CXenoInsDlg::OnFileBrowse() 
{
	CFileDialog dlg(TRUE);
	dlg.DoModal();

	CEdit ed;
	ed.Attach(GetDlgItem(IDC_ED_FILE)->m_hWnd);
	ed.SetWindowText(dlg.GetPathName());
	ed.Detach();
	
}
