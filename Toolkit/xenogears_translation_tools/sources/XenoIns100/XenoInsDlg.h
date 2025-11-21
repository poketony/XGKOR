// XenoInsDlg.h : header file
//

#if !defined(AFX_XENOINSDLG_H__57026806_9147_11D7_BD86_00E098852DE0__INCLUDED_)
#define AFX_XENOINSDLG_H__57026806_9147_11D7_BD86_00E098852DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>


/////////////////////////////////////////////////////////////////////////////
// CXenoInsDlg dialog

typedef struct{
	DWORD	dwStartSector;
	UINT	nLength;
}TOCEntry;

typedef CArray<TOCEntry, TOCEntry> CTOCArray;


class CXenoInsDlg : public CDialog
{
// Construction
public:
	CXenoInsDlg(CWnd* pParent = NULL);	// standard constructor
	CTOCArray arTOC;
// Dialog Data
	//{{AFX_DATA(CXenoInsDlg)
	enum { IDD = IDD_XENOINS_DIALOG };
	BOOL	m_bFix;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXenoInsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	BOOL WriteSector(CFile* file, BYTE *pBuffer, DWORD dwStart, UINT nNumOfSectors);
	BOOL ReadSector(CFile* file, BYTE* pBuffer, DWORD dwStart, UINT nNumOfSectors);

	// Generated message map functions
	//{{AFX_MSG(CXenoInsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnIsoBrowse();
	afx_msg void OnFileBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL WriteFile(CFile *iso, CFile *file, UINT nPosition);
	BOOL ReadVirtualTOC(CFile* file);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XENOINSDLG_H__57026806_9147_11D7_BD86_00E098852DE0__INCLUDED_)
