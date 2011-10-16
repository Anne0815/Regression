// mfcdemoView.h : interface of the CMfcdemoView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#include "ChartViewer.h"

#if !defined(AFX_MFCDEMOVIEW_H__95C92065_1A25_4B77_8E63_499A368363BA__INCLUDED_)
#define AFX_MFCDEMOVIEW_H__95C92065_1A25_4B77_8E63_499A368363BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMfcdemoView : public CFormView
{
protected: // create from serialization only
	CMfcdemoView();
	DECLARE_DYNCREATE(CMfcdemoView)

public:
	//{{AFX_DATA(CMfcdemoView)
	enum { IDD = IDD_MFCDEMO_FORM };
	CChartViewer m_ChartViewer7;
	CChartViewer m_ChartViewer6; 
	CChartViewer m_ChartViewer5;
	CChartViewer m_ChartViewer4;
	CChartViewer m_ChartViewer3;
	CChartViewer m_ChartViewer2;
	CChartViewer m_ChartViewer1;
	CChartViewer m_ChartViewer0;
	CListBox m_ChartList;
	//}}AFX_DATA

// Attributes
public:
	CMfcdemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcdemoView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcdemoView)
	afx_msg void OnSelchangeChartList();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChartClick(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	// Flow layout the charts
	void layoutCharts();
	// An array to hold the 8 CChartViewer objects in the demo to facilitate
	// processing using loops.
	CChartViewer* m_ChartViewer[8];
};

#ifndef _DEBUG  // debug version in mfcdemoView.cpp
inline CMfcdemoDoc* CMfcdemoView::GetDocument()
   { return (CMfcdemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDEMOVIEW_H__95C92065_1A25_4B77_8E63_499A368363BA__INCLUDED_)
