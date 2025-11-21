// XenoIns.h : main header file for the XENOINS application
//

#if !defined(AFX_XENOINS_H__57026804_9147_11D7_BD86_00E098852DE0__INCLUDED_)
#define AFX_XENOINS_H__57026804_9147_11D7_BD86_00E098852DE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXenoInsApp:
// See XenoIns.cpp for the implementation of this class
//

class CXenoInsApp : public CWinApp
{
public:
	CXenoInsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXenoInsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXenoInsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XENOINS_H__57026804_9147_11D7_BD86_00E098852DE0__INCLUDED_)
