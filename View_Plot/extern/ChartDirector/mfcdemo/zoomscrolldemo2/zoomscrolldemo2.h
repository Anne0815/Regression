// zoomscrolldemo2.h : main header file for the ZOOMSCROLLDEMO2 application
//

#if !defined(AFX_ZOOMSCROLLDEMO2_H__BA845E21_29E8_4462_B120_8D25A8C7CCE7__INCLUDED_)
#define AFX_ZOOMSCROLLDEMO2_H__BA845E21_29E8_4462_B120_8D25A8C7CCE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZoomscrolldemo2App:
// See zoomscrolldemo2.cpp for the implementation of this class
//

class CZoomscrolldemo2App : public CWinApp
{
public:
	CZoomscrolldemo2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomscrolldemo2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZoomscrolldemo2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMSCROLLDEMO2_H__BA845E21_29E8_4462_B120_8D25A8C7CCE7__INCLUDED_)
