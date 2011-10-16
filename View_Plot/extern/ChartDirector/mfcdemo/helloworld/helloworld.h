// helloworld.h : main header file for the HELLOWORLD application
//

#if !defined(AFX_HELLOWORLD_H__4DE26F03_0629_40F9_8F7E_85335F0E36E0__INCLUDED_)
#define AFX_HELLOWORLD_H__4DE26F03_0629_40F9_8F7E_85335F0E36E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHelloworldApp:
// See helloworld.cpp for the implementation of this class
//

class CHelloworldApp : public CWinApp
{
public:
	CHelloworldApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelloworldApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHelloworldApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELLOWORLD_H__4DE26F03_0629_40F9_8F7E_85335F0E36E0__INCLUDED_)
