#if !defined(AFX_IMAGEDLG_H__D651FF80_8CA9_11D9_916E_00E098852DE0__INCLUDED_)
#define AFX_IMAGEDLG_H__D651FF80_8CA9_11D9_916E_00E098852DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageDlg dialog

class CImageDlg : public CDialog
{
// Construction
public:
	BOOL ShowImage();
	BOOL DeleteImage();
	void AddPiece(CRect src, CPoint dst, BOOL hFlip = FALSE, BOOL vFlip = FALSE);
	void OpenRawFile(CString strFile, UINT nWidth);
	CImageDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImageDlg)
	enum { IDD = IDD_IMAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strImagePath;
	UINT m_nRawWidth;
	BYTE* m_data;
	BYTE m_image[256*256];
	CBitmap m_bitmap;
	// Generated message map functions
	//{{AFX_MSG(CImageDlg)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int memswap(BYTE* buff, UINT nLen);
	int memor(BYTE* dst, BYTE* src, int nCount);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEDLG_H__D651FF80_8CA9_11D9_916E_00E098852DE0__INCLUDED_)
