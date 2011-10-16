// zoomscrolldemo2Dlg.h : header file
//

#if !defined(AFX_ZOOMSCROLLDEMO2DLG_H__7EDE5AA2_52AA_4534_9DED_29A9C91CF2DF__INCLUDED_)
#define AFX_ZOOMSCROLLDEMO2DLG_H__7EDE5AA2_52AA_4534_9DED_29A9C91CF2DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChartViewer.h"
#include "RepeatButton.h"
#include "DragRect.h"
#include <afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// CZoomscrolldemo2Dlg dialog

class CZoomscrolldemo2Dlg : public CDialog
{
public:
// Construction
	CZoomscrolldemo2Dlg(CWnd* pParent = NULL);	// standard constructor
	~CZoomscrolldemo2Dlg();

// Dialog Data
	//{{AFX_DATA(CZoomscrolldemo2Dlg)
	enum { IDD = IDD_ZOOMSCROLLDEMO2_DIALOG };
	CButton	m_CenterPB;
	CButton	m_PointerPB;
	CStatic	m_NavigatePad;
	CDragRect	m_NavigateWindow;
	CSliderCtrl	m_ZoomBar;
	CRepeatButton	m_UpRightPB;
	CRepeatButton	m_UpPB;
	CRepeatButton	m_UpLeftPB;
	CRepeatButton	m_RightPB;
	CRepeatButton	m_LeftPB;
	CRepeatButton	m_DownRightPB;
	CRepeatButton	m_DownPB;
	CRepeatButton	m_DownLeftPB;
	CChartViewer	m_ChartViewer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomscrolldemo2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZoomscrolldemo2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPointerPB();
	afx_msg void OnZoomInPB();
	afx_msg void OnZoomOutPB();
	afx_msg void OnLeftPB();
	afx_msg void OnRightPB();
	afx_msg void OnUpPB();
	afx_msg void OnDownPB();
	afx_msg void OnUpLeftPB();
	afx_msg void OnDownLeftPB();
	afx_msg void OnUpRightPB();
	afx_msg void OnDownRightPB();
	afx_msg void OnCenterPB();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnNavigateWindow();
	afx_msg void OnDestroy();
	afx_msg void OnChartViewer();
	afx_msg void OnViewPortChanged();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
private:
	int m_extBgColor;	// The default background color.
	double m_minX;		// The minimum overall x scale
	double m_maxX;		// The maximum overall x scale
	double m_minY;		// The minimum overall y scale
	double m_maxY;		// The maximum overall y scale

	// Draw chart
	void drawChart(CChartViewer *viewer);
	// Update image map 
	void updateImageMap(CChartViewer *viewer);
	
	// handles the navigate buttons
	void handleButton(CRepeatButton *b, double deltaX, double deltaY);

	// utility to get default background color
	int getDefaultBgColor();
	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMSCROLLDEMO2DLG_H__7EDE5AA2_52AA_4534_9DED_29A9C91CF2DF__INCLUDED_)
