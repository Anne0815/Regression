// realtimedemo.h : main header file for the REALTIMEDEMO application
//

#if !defined(AFX_REALTIMEDEMO_H__FC3E83B9_4392_471C_8A6D_9B5FF1C14766__INCLUDED_)
#define AFX_REALTIMEDEMO_H__FC3E83B9_4392_471C_8A6D_9B5FF1C14766__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRealtimedemoApp:
// See realtimedemo.cpp for the implementation of this class
//

class CRealtimedemoApp : public CWinApp
{
public:
	CRealtimedemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealtimedemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRealtimedemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEDEMO_H__FC3E83B9_4392_471C_8A6D_9B5FF1C14766__INCLUDED_)
