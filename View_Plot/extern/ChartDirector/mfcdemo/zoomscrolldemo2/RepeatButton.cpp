// RepeatButton.cpp : implementation file
//

#include "stdafx.h"
#include "zoomscrolldemo2.h"
#include "RepeatButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRepeatButton
//
// A simple control that sents BN_CLICKED repeatedly to its parent when it is being pressed.
//

CRepeatButton::CRepeatButton()
{
	m_RepeatInterval = 100;
	m_ButtonIsPressed = false;
}

BEGIN_MESSAGE_MAP(CRepeatButton, CButton)
	//{{AFX_MSG_MAP(CRepeatButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRepeatButton message handlers

//
// Mouse down event handler - sets a timer to repeated sends BN_CLICKED messages to parent.
//
void CRepeatButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_ButtonIsPressed = true;
	SetTimer(1, m_RepeatInterval, 0);
	CButton::OnLButtonDown(nFlags, point);
}

//
// Mouse up event handler - kills the message timer.
//
void CRepeatButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_ButtonIsPressed = false;
	KillTimer(1);
	GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	CButton::OnLButtonUp(nFlags, point);
}

//
// Handles message timer. Sends BN_CLICKED message to parent
//
void CRepeatButton::OnTimer(ONTIMER_TYPE nIDEvent) 
{
	GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
	CButton::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// CRepeatButton properties

//
// Set repeat interval in milliseconds
//
void CRepeatButton::setRepeatInterval(int ms)
{
	m_RepeatInterval = ms;
}

//
// Get repeat interval in milliseconds
//
int CRepeatButton::getRepeatInterval()
{
	return m_RepeatInterval;
}

//
// Check if button is current being pressed
//
bool CRepeatButton::isPressed()
{
	return m_ButtonIsPressed;
}
