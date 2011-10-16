// zoomscrolldemo.h : main header file for the ZOOMSCROLLDEMO application
//

#if !defined(AFX_ZOOMSCROLLDEMO_H__CB755EA8_62C5_43AC_93B9_3F4024595A97__INCLUDED_)
#define AFX_ZOOMSCROLLDEMO_H__CB755EA8_62C5_43AC_93B9_3F4024595A97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZoomscrolldemoApp:
// See zoomscrolldemo.cpp for the implementation of this class
//

class CZoomscrolldemoApp : public CWinApp
{
public:
	CZoomscrolldemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomscrolldemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZoomscrolldemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMSCROLLDEMO_H__CB755EA8_62C5_43AC_93B9_3F4024595A97__INCLUDED_)
