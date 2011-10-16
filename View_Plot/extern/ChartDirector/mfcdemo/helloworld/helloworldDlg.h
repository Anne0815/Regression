// helloworldDlg.h : header file
//

#if !defined(AFX_HELLOWORLDDLG_H__A282BB99_2225_4AE8_AC43_0C5554FAEF55__INCLUDED_)
#define AFX_HELLOWORLDDLG_H__A282BB99_2225_4AE8_AC43_0C5554FAEF55__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChartViewer.h"

/////////////////////////////////////////////////////////////////////////////
// CHelloworldDlg dialog

class CHelloworldDlg : public CDialog
{
// Construction
public:
	CHelloworldDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHelloworldDlg)
	enum { IDD = IDD_HELLOWORLD_DIALOG };
	CChartViewer	m_ChartViewer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelloworldDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHelloworldDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELLOWORLDDLG_H__A282BB99_2225_4AE8_AC43_0C5554FAEF55__INCLUDED_)
