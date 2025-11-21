// xenomapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "xenomap.h"
#include "xenomapDlg.h"

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
// CXenomapDlg dialog

CXenomapDlg::CXenomapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXenomapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXenomapDlg)
	m_nImageX = 0;
	m_nImageY = 0;
	m_nSizeX = 0;
	m_nSizeY = 0;
	m_nScreenX = 0;
	m_nScreenY = 0;
	m_strUnknownData = _T("");
	m_strRawPath = _T("");
	m_nOrigineX = 0;
	m_nOrigineY = 0;
	m_bVFlip = FALSE;
	m_bHFlip = FALSE;
	m_nImageNum = 0;
	m_nPieceNum = 0;
	m_bViewAll = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINACCEL));
	m_bSpinImage = FALSE;
	m_bSpinPiece = FALSE;
}

void CXenomapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXenomapDlg)
	DDX_Text(pDX, IDC_IMAGEX, m_nImageX);
	DDX_Text(pDX, IDC_IMAGEY, m_nImageY);
	DDX_Text(pDX, IDC_SIZEX, m_nSizeX);
	DDX_Text(pDX, IDC_SIZEY, m_nSizeY);
	DDX_Text(pDX, IDC_SCREENX, m_nScreenX);
	DDX_Text(pDX, IDC_SCREENY, m_nScreenY);
	DDX_Text(pDX, IDC_UNKNOWN, m_strUnknownData);
	DDV_MaxChars(pDX, m_strUnknownData, 32);
	DDX_Text(pDX, IDC_RAWPATH, m_strRawPath);
	DDX_Text(pDX, IDC_XORIGINE, m_nOrigineX);
	DDX_Text(pDX, IDC_YORIGINE, m_nOrigineY);
	DDX_Check(pDX, IDC_VFLIP, m_bVFlip);
	DDX_Check(pDX, IDC_HFLIP, m_bHFlip);
	DDX_Control(pDX, IDC_PIECENUM, m_edImagePiece);
	DDX_Text(pDX, IDC_IMAGENUM, m_nImageNum);
	DDX_Text(pDX, IDC_PIECENUM, m_nPieceNum);
	DDX_Control(pDX, IDC_IMAGENUM, m_edImageNum);
	DDX_Check(pDX, IDC_VIEWALL, m_bViewAll);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXenomapDlg, CDialog)
	//{{AFX_MSG_MAP(CXenomapDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_APRI, OnFileApri)
	ON_COMMAND(ACC_RETURN, OnPressEnter)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINIMAGE, OnDeltaposSpinimage)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPINPIECE, OnDeltaposSpinpiece)
	ON_EN_CHANGE(IDC_IMAGENUM, OnChangeImagenum)
	ON_EN_CHANGE(IDC_PIECENUM, OnChangePiecenum)
	ON_EN_KILLFOCUS(IDC_IMAGEX, OnKillfocusImagex)
	ON_EN_KILLFOCUS(IDC_IMAGEY, OnKillfocusImagey)
	ON_EN_KILLFOCUS(IDC_SCREENX, OnKillfocusScreenx)
	ON_EN_KILLFOCUS(IDC_SCREENY, OnKillfocusScreeny)
	ON_EN_KILLFOCUS(IDC_SIZEX, OnKillfocusSizex)
	ON_EN_KILLFOCUS(IDC_SIZEY, OnKillfocusSizey)
	ON_EN_KILLFOCUS(IDC_UNKNOWN, OnKillfocusUnknown)
	ON_COMMAND(ID_FILE_SALVACONNOME, OnFileSalvaconnome)
	ON_BN_CLICKED(IDC_ADD, OnAddElement)
	ON_BN_CLICKED(IDC_REMOVE, OnRemoveElement)
	ON_BN_CLICKED(IDC_OPENRAW, OnOpenraw)
	ON_BN_CLICKED(IDC_RENDER, OnRender)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_SALVA, OnFileSalva)
	ON_UPDATE_COMMAND_UI(ID_FILE_SALVA, OnUpdateFileSalva)
	ON_UPDATE_COMMAND_UI(ID_FILE_SALVACONNOME, OnUpdateFileSalvaconnome)
	ON_BN_CLICKED(IDC_HFLIP, OnHflip)
	ON_BN_CLICKED(IDC_VFLIP, OnVflip)
	ON_COMMAND(ID_FILE_ESCI, OnFileEsci)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXenomapDlg message handlers

BOOL CXenomapDlg::OnInitDialog()
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

	m_pathname = "";
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXenomapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CXenomapDlg::OnPaint() 
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
HCURSOR CXenomapDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CXenomapDlg::PreTranslateMessage(MSG* pMsg) 
{
	
	if (m_hAccel != NULL)
		if (::TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
			return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CXenomapDlg::OnFileApri() 
{
	CFileDialog dlg(TRUE);
	
	if (dlg.DoModal() == IDOK){
		CFile file;
		BYTE* data;
		m_pathname = dlg.GetPathName();
		file.Open(dlg.GetPathName(), CFile::modeRead);
		data = new BYTE[file.GetLength()];
		file.Read(data, file.GetLength());
		file.Close();
		ReadData(data);
		delete[] data;

		//
		//Inizializzazione
		//
		CSpinButtonCtrl spin;
		spin.Attach(GetDlgItem(IDC_SPINIMAGE)->m_hWnd);
		spin.SetRange(0,m_image.GetUpperBound());
		spin.Detach();
		
		CString s;
		s.Format("%d",m_image.GetUpperBound());
		CEdit ed;
		ed.Attach(GetDlgItem(IDC_IMAGENUMMAX)->m_hWnd);
		ed.SetWindowText(s);
		ed.Detach();

		EnableAll(TRUE);

		if (m_strRawPath != ""){
			CButton bt;
			bt.Attach(GetDlgItem(IDC_RENDER)->m_hWnd);
			bt.EnableWindow();
			bt.Detach();
		}


		SetImage();
	}
}

void CXenomapDlg::ReadData(BYTE *data)
{
	m_image.RemoveAll();

	DWORD size = 0;
	
	memcpy(&size,data,4);
	
	m_image.SetSize(size);
	for (UINT i=0;i<size;i++){
		UINT pointer = 0;
		memcpy(&pointer, data+4+i*2,2);
		m_image[i].setData(data+pointer);
	}

}

void CXenomapDlg::OnPressEnter() 
{
	if (GetFocus()->m_hWnd == m_edImageNum.m_hWnd){
		SetImage();
	}
	else if (GetFocus()->m_hWnd == m_edImagePiece.m_hWnd){
		SetPiece();
	}

}

void CXenomapDlg::OnDeltaposSpinimage(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	m_bSpinImage = TRUE;	
	*pResult = 0;
}

void CXenomapDlg::OnDeltaposSpinpiece(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	m_bSpinPiece = TRUE;	
	*pResult = 0;
}

UINT CXenomapDlg::SetImage()
{
	UpdateData(TRUE);
	
	m_nPieceNum = 0;

	CMappedImage mi= m_image.GetAt(m_nImageNum);

	CSpinButtonCtrl spin;
	spin.Attach(GetDlgItem(IDC_SPINPIECE)->m_hWnd);
	spin.SetRange(0,mi.getSize());
	spin.Detach();


	CString s;
	s.Format("%d",mi.getSize());
	CEdit ed;
	ed.Attach(GetDlgItem(IDC_PIECENUMMAX)->m_hWnd);
	ed.SetWindowText(s);
	ed.Detach();


	UpdateData(FALSE);
	SetPiece();

	return 1;
}

void CXenomapDlg::OnChangeImagenum() 
{
	if (m_bSpinImage){
		m_bSpinImage=FALSE;
		SetImage();	
	}
}

void CXenomapDlg::OnChangePiecenum() 
{
	if (m_bSpinPiece){
		m_bSpinPiece=FALSE;
		SetPiece();	
	}
	
}

UINT CXenomapDlg::SetPiece()
{
	UpdateData(TRUE);

	if ((INT)m_nImageNum > m_image.GetUpperBound())
		m_nImageNum = m_image.GetUpperBound();

	CMappedImage mi = m_image.GetAt(m_nImageNum);

	if (m_nPieceNum == 0){
		ResetAllFields();
		return 0;
	}

	if (m_nPieceNum > mi.getSize())
		m_nPieceNum = mi.getSize();

	
	CMapData md = mi.getAt(m_nPieceNum-1);
	
	m_nImageX = md.getXOffsetImage();
	m_nImageY = md.getYOffsetImage();
	m_nSizeX = md.getWidth();
	m_nSizeY = md.getHeight();
	m_nScreenX = md.getXOffsetScreen();
	m_nScreenY = md.getYOffsetScreen();
	BYTE ud[16];
	md.getUnknownData(ud);
	m_strUnknownData="";
	m_strUnknownData.Format("%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X",
		ud[0],ud[1],ud[2],ud[3],ud[4],ud[5],ud[6],ud[7],ud[8],ud[9],ud[10],ud[11],ud[12],ud[13],ud[14]);
	
	m_bHFlip = md.isFlippedX();
	m_bVFlip = md.isFlippedY();

	UpdateData(FALSE);
	return 1;
}

void CXenomapDlg::ResetAllFields()
{
	m_nImageX = 0;
	m_nImageY = 0;
	m_nSizeX = 0;
	m_nSizeY = 0;
	m_nScreenX = 0;
	m_nScreenY = 0;
	m_strUnknownData = "";	

	UpdateData(FALSE);

}

void CXenomapDlg::OnKillfocusImagex() 
{
	UpdateData(TRUE);
	CMappedImage mi = m_image.GetAt(m_nImageNum);
	CMapData md = mi.getAt(m_nPieceNum-1);

	md.setXOffsetImage(m_nImageX);

	mi.setAt(m_nPieceNum-1, md);
	m_image[m_nImageNum] = mi;
}



void CXenomapDlg::OnKillfocusImagey() 
{
	UpdateData(TRUE);
	CMappedImage mi = m_image.GetAt(m_nImageNum);
	CMapData md = mi.getAt(m_nPieceNum-1);

	md.setYOffsetImage(m_nImageY);

	mi.setAt(m_nPieceNum-1, md);
	m_image[m_nImageNum] = mi;	
}

void CXenomapDlg::OnKillfocusScreenx() 
{
	UpdateData(TRUE);
	CMappedImage mi = m_image.GetAt(m_nImageNum);
	CMapData md = mi.getAt(m_nPieceNum-1);

	md.setXOffsetScreen(m_nScreenX);

	mi.setAt(m_nPieceNum-1, md);
	m_image[m_nImageNum] = mi;	
}

void CXenomapDlg::OnKillfocusScreeny() 
{
	UpdateData(TRUE);
	CMappedImage mi = m_image.GetAt(m_nImageNum);
	CMapData md = mi.getAt(m_nPieceNum-1);

	md.setYOffsetScreen(m_nScreenY);

	mi.setAt(m_nPieceNum-1, md);
	m_image[m_nImageNum] = mi;	
	
}

void CXenomapDlg::OnKillfocusSizex() 
{
	UpdateData(TRUE);
	CMappedImage mi = m_image.GetAt(m_nImageNum);
	CMapData md = mi.getAt(m_nPieceNum-1);

	md.setWidth(m_nSizeX);

	mi.setAt(m_nPieceNum-1, md);
	m_image[m_nImageNum] = mi;	
	
}

void CXenomapDlg::OnKillfocusSizey() 
{
	UpdateData(TRUE);
	CMappedImage mi = m_image.GetAt(m_nImageNum);
	CMapData md = mi.getAt(m_nPieceNum-1);

	md.setHeight(m_nSizeY);

	mi.setAt(m_nPieceNum-1, md);
	m_image[m_nImageNum] = mi;	
	
}

void CXenomapDlg::OnKillfocusUnknown() 
{
	UpdateData(TRUE);
	CMappedImage mi = m_image.GetAt(m_nImageNum);
	CMapData md = mi.getAt(m_nPieceNum-1);

	if (m_strUnknownData.GetLength() != 28){
		AfxMessageBox("Errore nei dati inseriti");
		return;
	}

	md.setUnknownData(m_strUnknownData);

	mi.setAt(m_nPieceNum-1, md);
	m_image[m_nImageNum] = mi;	
	
}

void CXenomapDlg::OnFileSalvaconnome() 
{
	CFileDialog dlg(FALSE);
	
	if (dlg.DoModal() == IDOK){
		if (!SaveFile(dlg.GetPathName()))
			AfxMessageBox("Errore in scrittura");
	}

}

void CXenomapDlg::OnAddElement() 
{
	UpdateData(TRUE);
	CMapData md;
	m_image[m_nImageNum].Add(md);
	SetImage();
	m_nPieceNum = m_image[m_nImageNum].getSize();
	UpdateData(FALSE);
	SetPiece();
}

void CXenomapDlg::OnRemoveElement() 
{
	UpdateData(TRUE);
	if (m_nPieceNum>0)
		m_image[m_nImageNum].RemoveAt(m_nPieceNum-1);
	SetImage();
}

void CXenomapDlg::OnOpenraw() 
{
	CFileDialog dlg(TRUE);
	
	if (dlg.DoModal()==IDOK){
		m_strRawPath = dlg.GetPathName();
	
		m_nOrigineX = 128;
		m_nOrigineY = 128;
		m_dlgImage.OpenRawFile(m_strRawPath, 256);	
	
		if (m_pathname != ""){
			CButton bt;
			bt.Attach(GetDlgItem(IDC_RENDER)->m_hWnd);
			bt.EnableWindow();
			bt.Detach();
		}


		UpdateData(FALSE);
	}
}

void CXenomapDlg::OnRender() 
{
	UpdateData();
	m_dlgImage.DeleteImage();
	CMappedImage mi = m_image[m_nImageNum];

	if ((m_bViewAll)||(m_nPieceNum == 0)){
	for(UINT i=0; i<mi.getSize(); i++){
			CMapData md = mi.getAt(i);
			CRect rect; CPoint point;
		
			rect.top = md.getYOffsetImage();
			rect.bottom = md.getYOffsetImage() +  md.getHeight();
			rect.left = md.getXOffsetImage();
			rect.right = md.getXOffsetImage() + md.getWidth();
			point.x = md.getXOffsetScreen() + m_nOrigineX;
			point.y=md.getYOffsetScreen() + m_nOrigineY;
			m_dlgImage.AddPiece(rect, point, md.isFlippedX(), md.isFlippedY());
		}
	}
	else{
		CMapData md = mi.getAt(m_nPieceNum);
		CRect rect; CPoint point;
		
		rect.top = md.getYOffsetImage();
		rect.bottom = md.getYOffsetImage() +  md.getHeight();
		rect.left = md.getXOffsetImage();
		rect.right = md.getXOffsetImage() + md.getWidth();
		point.x = md.getXOffsetScreen() + m_nOrigineX;
		point.y=md.getYOffsetScreen() + m_nOrigineY;
		m_dlgImage.AddPiece(rect, point, md.isFlippedX(), md.isFlippedY());
	}
	m_dlgImage.ShowWindow(SW_SHOW);
	m_dlgImage.ShowImage();
}

int CXenomapDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_dlgImage.Create(IDD_IMAGE, this);
	m_dlgImage.ShowWindow(SW_HIDE);
	
	return 0;
}

BOOL CXenomapDlg::EnableAll(BOOL bEnable)
{
	CEdit ed;

	ed.Attach(GetDlgItem(IDC_IMAGEX)->m_hWnd);
	ed.EnableWindow(bEnable);
	ed.Detach();

	ed.Attach(GetDlgItem(IDC_IMAGEY)->m_hWnd);
	ed.EnableWindow(bEnable);
	ed.Detach();

	ed.Attach(GetDlgItem(IDC_SIZEX)->m_hWnd);
	ed.EnableWindow(bEnable);
	ed.Detach();

	ed.Attach(GetDlgItem(IDC_SIZEY)->m_hWnd);
	ed.EnableWindow(bEnable);
	ed.Detach();

	ed.Attach(GetDlgItem(IDC_SCREENX)->m_hWnd);
	ed.EnableWindow(bEnable);
	ed.Detach();

	ed.Attach(GetDlgItem(IDC_SCREENY)->m_hWnd);
	ed.EnableWindow(bEnable);
	ed.Detach();

	ed.Attach(GetDlgItem(IDC_UNKNOWN)->m_hWnd);
	ed.EnableWindow(bEnable);
	ed.Detach();
	
	m_edImagePiece.EnableWindow(bEnable);
	m_edImageNum.EnableWindow(bEnable);

	CSpinButtonCtrl spin;

	spin.Attach(GetDlgItem(IDC_SPINIMAGE)->m_hWnd);
	spin.EnableWindow(bEnable);
	spin.Detach();

	spin.Attach(GetDlgItem(IDC_SPINPIECE)->m_hWnd);
	spin.EnableWindow(bEnable);
	spin.Detach();


	CButton bt;

	bt.Attach(GetDlgItem(IDC_ADD)->m_hWnd);
	bt.EnableWindow(bEnable);
	bt.Detach();

	bt.Attach(GetDlgItem(IDC_REMOVE)->m_hWnd);
	bt.EnableWindow(bEnable);
	bt.Detach();

	bt.Attach(GetDlgItem(IDC_HFLIP)->m_hWnd);
	bt.EnableWindow(bEnable);
	bt.Detach();

	bt.Attach(GetDlgItem(IDC_VFLIP)->m_hWnd);
	bt.EnableWindow(bEnable);
	bt.Detach();

	bt.Attach(GetDlgItem(IDC_VIEWALL)->m_hWnd);
	bt.EnableWindow(bEnable);
	bt.Detach();


	return TRUE;
}

void CXenomapDlg::OnFileSalva() 
{
	if (!SaveFile(m_pathname))
		AfxMessageBox("Errore in scrittura");
}

BOOL CXenomapDlg::SaveFile(CString strfilename)
{
	CFile file;
	CFileException e;
	file.Open(strfilename, CFile::modeCreate | CFile::modeWrite, &e);
	try{
		BYTE* index;
		UINT indexlen = 2 * m_image.GetSize() + 4;
		index = new BYTE[indexlen];
		file.Write(index, indexlen);	//scrivo indice fittizio (alla fine va sovrascritto)
		UINT num = m_image.GetSize();
		memcpy(index, &num, 4);
		UINT pointer = num*2+4;		//valore iniziale del pointer
		for (UINT i=0; i<num; i++){
			memcpy(index + 4 +i*2, &pointer, 2);
		BYTE* data;
			UINT len = m_image[i].getLength();
			pointer += len;	
			data = new BYTE[len];
			m_image[i].getData(data);
			file.Write(data,len);
		}
		file.SeekToBegin();
		file.Write(index,indexlen);
		file.Close();
	}
	catch (CFileException e){
		return FALSE;
	}
	return TRUE;
}

void CXenomapDlg::OnUpdateFileSalva(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pathname != "");	
	
}

void CXenomapDlg::OnUpdateFileSalvaconnome(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_pathname != "");	
}

void CXenomapDlg::OnHflip() 
{
	UpdateData();

	CMappedImage mi = m_image.GetAt(m_nImageNum);
	CMapData md = mi.getAt(m_nPieceNum-1);
	
	md.setFlipX(m_bHFlip);

	mi.setAt(m_nPieceNum-1, md);
	m_image[m_nImageNum] = mi;

}

void CXenomapDlg::OnVflip() 
{
	UpdateData();

	CMappedImage mi = m_image.GetAt(m_nImageNum);
	CMapData md = mi.getAt(m_nPieceNum-1);
	
	md.setFlipY(m_bVFlip);
	mi.setAt(m_nPieceNum-1, md);
	m_image[m_nImageNum] = mi;
	
}

void CXenomapDlg::OnFileEsci() 
{
	this->DestroyWindow();	
}
