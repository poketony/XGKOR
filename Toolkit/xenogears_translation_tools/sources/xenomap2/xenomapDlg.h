// xenomapDlg.h : header file
//

#if !defined(AFX_XENOMAPDLG_H__651D4366_8371_11D9_916E_00E098852DE0__INCLUDED_)
#define AFX_XENOMAPDLG_H__651D4366_8371_11D9_916E_00E098852DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXenomapDlg dialog

#include <afxtempl.h>
#include "mappedimage.h"
#include "imagedlg.h"

class CXenomapDlg : public CDialog
{
typedef CArray<CMappedImage, CMappedImage> CMappedImageArray;

// Construction
public:
	BOOL EnableAll(BOOL bEnable);
	void ReadData(BYTE* data);
	CXenomapDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXenomapDlg)
	enum { IDD = IDD_XENOMAP_DIALOG };
	UINT	m_nImageX;
	UINT	m_nImageY;
	UINT	m_nSizeX;
	UINT	m_nSizeY;
	INT		m_nScreenX;
	INT		m_nScreenY;
	CString	m_strUnknownData;
	CString	m_strRawPath;
	INT	m_nOrigineX;
	INT	m_nOrigineY;
	BOOL	m_bVFlip;
	BOOL	m_bHFlip;
	BOOL	m_bViewAll;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXenomapDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL SaveFile(CString strfilename);
	void ResetAllFields();
	UINT	SetPiece();
	UINT	SetImage();
	CEdit	m_edImagePiece;
	UINT	m_nImageNum;
	UINT	m_nPieceNum;
	CEdit	m_edImageNum;
	BOOL	m_bSpinPiece;
	BOOL	m_bSpinImage;
	CString m_pathname;
	HACCEL	m_hAccel;
	HICON	m_hIcon;
	CImageDlg m_dlgImage;

	CMappedImageArray m_image;
	// Generated message map functions
	//{{AFX_MSG(CXenomapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileApri();
	afx_msg void OnPressEnter();
	afx_msg void OnDeltaposSpinimage(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinpiece(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeImagenum();
	afx_msg void OnChangePiecenum();
	afx_msg void OnKillfocusImagex();
	afx_msg void OnKillfocusImagey();
	afx_msg void OnKillfocusScreenx();
	afx_msg void OnKillfocusScreeny();
	afx_msg void OnKillfocusSizex();
	afx_msg void OnKillfocusSizey();
	afx_msg void OnKillfocusUnknown();
	afx_msg void OnFileSalvaconnome();
	afx_msg void OnAddElement();
	afx_msg void OnRemoveElement();
	afx_msg void OnOpenraw();
	afx_msg void OnRender();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFileSalva();
	afx_msg void OnUpdateFileSalva(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSalvaconnome(CCmdUI* pCmdUI);
	afx_msg void OnHflip();
	afx_msg void OnVflip();
	afx_msg void OnFileEsci();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XENOMAPDLG_H__651D4366_8371_11D9_916E_00E098852DE0__INCLUDED_)
