#if !defined(AFX_DRAGRECT_H__37450691_7509_4FD1_9E8B_F62F41BF3C5A__INCLUDED_)
#define AFX_DRAGRECT_H__37450691_7509_4FD1_9E8B_F62F41BF3C5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DragRect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDragRect window
//
// A simple control that sents BN_CLICKED message to its parent when it is being dragged. The 
// parent can then call the control methods to get the drag parameters.
//

class CDragRect : public CStatic
{
public:
// Construction
	CDragRect();

// Public interface
	virtual bool IsMouseDown() ;
	virtual CPoint GetMouseDownPos();
	virtual bool IsMouseDrag();
	virtual CPoint GetMouseDragPos();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragRect)
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDragRect)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
#if _MSC_VER >= 1400
	afx_msg LRESULT OnNcHitTest(CPoint point);
#else
	afx_msg UINT OnNcHitTest(CPoint point);
#endif 
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	bool m_IsMouseDown;
	CPoint m_MouseDownPos;
	bool m_IsMouseDrag;
	CPoint m_MouseDragPos;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGRECT_H__37450691_7509_4FD1_9E8B_F62F41BF3C5A__INCLUDED_)
