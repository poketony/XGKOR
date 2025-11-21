// ImageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "xenomap.h"
#include "ImageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageDlg dialog


CImageDlg::CImageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_data=NULL;
}


void CImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageDlg, CDialog)
	//{{AFX_MSG_MAP(CImageDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageDlg message handlers

void CImageDlg::OpenRawFile(CString strFile, UINT nWidth)
{
	if (m_data != NULL)
		delete[] m_data;

	CFile file;
	file.Open(strFile, CFile::modeRead);
	m_data= new BYTE[file.GetLength()];
	file.Read(m_data, file.GetLength());
	file.Close();
	m_nRawWidth = nWidth;
	DeleteImage();
}

void CImageDlg::PostNcDestroy() 
{
	if (m_data != NULL)
		delete[] m_data;
	CDialog::PostNcDestroy();
}

void CImageDlg::AddPiece(CRect src, CPoint dst, BOOL hFlip, BOOL vFlip)
{
	int i=0, j=0;
	BYTE* row;
	
	row = new BYTE[src.Width()];
	if (!vFlip){
		for (i=0; i<src.Height(); i++){
			memcpy(row, m_data+(src.top+i)*m_nRawWidth+src.left, src.Width());
			if (hFlip) memswap(row,src.Width());
			memor(m_image + (dst.y+i)*256 + dst.x, row, src.Width());
		}
	}
	else{
		for (i=0; i<src.Height(); i++){
			memcpy(row, m_data+(src.top+i)*m_nRawWidth+src.left, src.Width());
			if (hFlip) memswap(row,src.Width());
			memor(m_image + (dst.y+src.Height()-1-i)*256 + dst.x, row, src.Width());
		}
	} 
}

BOOL CImageDlg::DeleteImage()
{
	memset(m_image,0,256*256);
	return TRUE;
}

BOOL CImageDlg::ShowImage()
{
	CClientDC cdc(this);
	m_bitmap.DeleteObject();

	BITMAPINFO* bmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER) + 4*256);
	bmi->bmiHeader.biBitCount = 8;
	bmi->bmiHeader.biClrImportant = 0;
	bmi->bmiHeader.biClrUsed = 256;
	bmi->bmiHeader.biCompression = BI_RGB;
	bmi->bmiHeader.biHeight = -256;
	bmi->bmiHeader.biPlanes = 1;
	bmi->bmiHeader.biSize = sizeof(bmi->bmiHeader);
	bmi->bmiHeader.biSizeImage = 0;
	bmi->bmiHeader.biWidth = 256;
	bmi->bmiHeader.biXPelsPerMeter = 0;
	bmi->bmiHeader.biYPelsPerMeter = 0;

	for (int i=0; i< 256; i++){
		bmi->bmiColors[i].rgbBlue =i;
		bmi->bmiColors[i].rgbGreen =i;
		bmi->bmiColors[i].rgbRed=i;
		bmi->bmiColors[i].rgbReserved=0;
	}

	m_bitmap.CreateCompatibleBitmap(&cdc, 256, 256);
	CDC destDC;
	destDC.CreateCompatibleDC(&cdc);
	SetDIBits((HDC)destDC,(HBITMAP)m_bitmap,0,256,m_image,bmi,DIB_RGB_COLORS);
	destDC.SelectObject(&m_bitmap);



	CRect rect(0,0,256,256);
	CalcWindowRect(&rect);
	SetWindowPos(NULL,0,0, rect.Width(), rect.Height(), SWP_NOZORDER|SWP_NOMOVE);
	
	cdc.BitBlt(0,0, 256, 256, &destDC, 0, 0, SRCCOPY);
	destDC.DeleteDC();
	free(bmi);
	return TRUE;
}

void CImageDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (m_data != NULL) ShowImage();	
	
	// Do not call CDialog::OnPaint() for painting messages
}

int CImageDlg::memor(BYTE *dst, BYTE *src, int nCount)
{
	for (int i=0; i<nCount; i++){
		dst[i] |= src[i];
	}
	return i;
}

int CImageDlg::memswap(BYTE *buff, UINT nLen)
{
	for (UINT i=0; i<=nLen/2; i++){
		int c=buff[nLen-i-1];
		buff[nLen-i] = buff[i];
		buff[i]=c;
	}
	return nLen;
}
