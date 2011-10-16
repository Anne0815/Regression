// zoomscrolldemoDlg.h : header file
//

#if !defined(AFX_ZOOMSCROLLDEMODLG_H__1D289C1E_2C9E_43C6_B6F4_CDE438051F6C__INCLUDED_)
#define AFX_ZOOMSCROLLDEMODLG_H__1D289C1E_2C9E_43C6_B6F4_CDE438051F6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChartViewer.h"
#include <afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// CZoomscrolldemoDlg dialog

const int sampleSize = 240;

class CZoomscrolldemoDlg : public CDialog
{
public:
// Construction
	CZoomscrolldemoDlg(CWnd* pParent = NULL);	// standard constructor
	~CZoomscrolldemoDlg();

// Dialog Data
	//{{AFX_DATA(CZoomscrolldemoDlg)
	enum { IDD = IDD_ZOOMSCROLLDEMO_DIALOG };
	CDateTimeCtrl	m_StartDate;
	CComboBox	m_Duration;
	CScrollBar	m_VScrollBar;
	CScrollBar	m_HScrollBar;
	CButton	m_XZoomPB;
	CButton	m_PointerPB;
	CChartViewer	m_ChartViewer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomscrolldemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CZoomscrolldemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPointerPB();
	afx_msg void OnZoomInPB();
	afx_msg void OnZoomOutPB();
	afx_msg void OnXZoomPB();
	afx_msg void OnXYZoomPB();
	afx_msg void OnChartViewer();
	afx_msg void OnViewPortChanged();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnDatetimechangeStartDate(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeDuration();
	afx_msg void OnKillfocusDuration();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()

	// Handles pressing the "Enter" key
	virtual void OnOK();

private:
	//
	// Data arrays for the scrollable / zoomable chart.
	// - In this demo, we just use a RanTable object to generate random data for the chart.
	//
	RanTable *m_dataTable;
	DoubleArray m_timeStamps;
	DoubleArray m_dataSeriesA;
	DoubleArray m_dataSeriesB;
	DoubleArray m_dataSeriesC;
	
	int m_extBgColor;			// The default background color

	double m_minDate;			// The earliest date (in chartTime unit)
	double m_dateRange;			// The overall duration (in seconds)
	double m_maxValue;			// The maximum overall y scale
	double m_minValue;			// The minimum overall y scale
	
	double m_currentDuration;	// The visible duration of the view port (in seconds)
	double m_minDuration;		// The maximum zoom-in limit (in seconds)

	// Load data into data arrays
	void loadData();
	
	// Draw chart
	void drawChart(CChartViewer *viewer);
	// Update image map 
	void updateImageMap(CChartViewer *viewer);

	// Moves the scroll bar when the user clicks on it
	double moveScrollBar(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// Validate the duration entered by the user
	void validateDuration(const CString &text);

	// utility to get default background color
	int getDefaultBgColor();
	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMSCROLLDEMODLG_H__1D289C1E_2C9E_43C6_B6F4_CDE438051F6C__INCLUDED_)
