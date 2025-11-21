// xenopatcherDlg.h : file di intestazione
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

#define WM_UPDATEBAR	WM_USER + 0x100
#define WM_THREADEND	WM_USER + 0x110

// finestra di dialogo CxenopatcherDlg
class CxenopatcherDlg : public CDialog
{
// Costruzione
public:
	CxenopatcherDlg(CWnd* pParent = NULL);	// costruttore standard

// Dati della finestra di dialogo
	enum { IDD = IDD_XENOPATCHER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// supporto DDX/DDV


// Implementazione
protected:
	HICON m_hIcon;

	// Funzioni generate per la mappa dei messaggi
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg long OnUpdateBar(WPARAM wParam, LPARAM lParam);
	afx_msg long OnThreadEnd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedBrowsepatch();
	afx_msg void OnBnClickedBtapply();
	void ShowContextHelp(CWnd* pWnd, POINT pt, int iCtrlID);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBrowseiso();
protected:
	CEdit m_edIso;
public:
	CString m_strIsoPath;
	CString m_strPatchPath;
	int ModifyName(CString* strPath);
	int DetectCD(unsigned char* index);
	CString m_strStatus;
private:
public:
	CString m_strVoice;
	int ApplyPatch(void);
	afx_msg void OnReturn();
	CProgressCtrl m_wndProgress;
	BOOL PreTranslateMessage(MSG* pMsg);
private:
	CBrush m_bRedBrush; 
	HACCEL m_hAccel;

public:
	afx_msg void OnAbout();
	afx_msg void OnFileEsci();
	CString m_strComm;
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	BOOL m_bBackup;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
