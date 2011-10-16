// DragRect.cpp : implementation file
//

#include "stdafx.h"
#include "zoomscrolldemo2.h"
#include "DragRect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragRect
//
// A simple control that sents BN_CLICKED message to its parent when it is being dragged. The 
// parent can then call the control methods to get the drag parameters.
//

//
// Constructor
//
CDragRect::CDragRect()
{
	m_IsMouseDown = false;
	m_IsMouseDrag = false;
}

BEGIN_MESSAGE_MAP(CDragRect, CStatic)
	//{{AFX_MSG_MAP(CDragRect)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragRect message handlers

//
// Hit testing message handler. In this control, the mouse always hits the client area.
//
#if _MSC_VER >= 1400
	afx_msg LRESULT CDragRect::OnNcHitTest(CPoint point)
#else
	afx_msg UINT CDragRect::OnNcHitTest(CPoint point)
#endif 
{
	return HTCLIENT;
}

//
// Mouse left button down event.
//
void CDragRect::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// Save the mouse down position and capture the mouse to prepare for dragging
	m_IsMouseDown = true;
	m_MouseDownPos = point;
	m_MouseDragPos = point;
	SetCapture();
	CStatic::OnLButtonDown(nFlags, point);
}

//
// Mouse over event
//
void CDragRect::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_IsMouseDown)
	{
		// Mouse is dragging - send BN_CLICK event to parent
		m_IsMouseDrag = true;
		m_MouseDragPos = point;
		GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	}
	CStatic::OnMouseMove(nFlags, point);
}

//
// Mouse left button up event
//
void CDragRect::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// Release mouse capture and reset mouse dragging flags
	m_IsMouseDown = false;
	m_IsMouseDrag = false;
	m_MouseDragPos = point;
	ReleaseCapture();
	GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	CStatic::OnLButtonUp(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CDragRect properties

// Check if left mouse button is in down state
bool CDragRect::IsMouseDown() 
{ 
	return m_IsMouseDown; 
}

// Get the point when the mouse is pressed down
CPoint CDragRect::GetMouseDownPos()
{
	return m_MouseDownPos;
}

// Check if mouse is dragging
bool CDragRect::IsMouseDrag()
{
	return m_IsMouseDrag;
}

// Get the current position of the mouse if it is dragging
CPoint CDragRect::GetMouseDragPos()
{
	return m_MouseDragPos;
}
