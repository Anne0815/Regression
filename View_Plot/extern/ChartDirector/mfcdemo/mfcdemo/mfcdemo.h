// mfcdemo.h : main header file for the MFCDEMO application
//

#if !defined(AFX_MFCDEMO_H__ACB8D7D1_B2BE_4362_983E_A8593C91E496__INCLUDED_)
#define AFX_MFCDEMO_H__ACB8D7D1_B2BE_4362_983E_A8593C91E496__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcdemoApp:
// See mfcdemo.cpp for the implementation of this class
//

class CMfcdemoApp : public CWinApp
{
public:
	CMfcdemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcdemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMfcdemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDEMO_H__ACB8D7D1_B2BE_4362_983E_A8593C91E496__INCLUDED_)
