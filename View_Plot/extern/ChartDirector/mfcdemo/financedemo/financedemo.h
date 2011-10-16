// financedemo.h : main header file for the FINANCEDEMO application
//

#if !defined(AFX_FINANCEDEMO_H__D13339B9_D8B6_40D0_8715_1D08DCF956FD__INCLUDED_)
#define AFX_FINANCEDEMO_H__D13339B9_D8B6_40D0_8715_1D08DCF956FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFinancedemoApp:
// See financedemo.cpp for the implementation of this class
//

class CFinancedemoApp : public CWinApp
{
public:
	CFinancedemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFinancedemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFinancedemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINANCEDEMO_H__D13339B9_D8B6_40D0_8715_1D08DCF956FD__INCLUDED_)
