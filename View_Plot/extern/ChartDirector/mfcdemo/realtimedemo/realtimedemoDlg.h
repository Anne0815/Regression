// realtimedemoDlg.h : header file
//

#if !defined(AFX_REALTIMEDEMODLG_H__BE2F0092_7DD2_4D82_991B_4CF30D500281__INCLUDED_)
#define AFX_REALTIMEDEMODLG_H__BE2F0092_7DD2_4D82_991B_4CF30D500281__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChartViewer.h"
#include <afxmt.h>

//
// The argument type used in OnTimer. In MFC, the argument is different in 
// Win32 and Win64.
//
#ifndef ONTIMER_TYPE_DEFINED
#define ONTIMER_TYPE_DEFINED

	#ifdef _WIN64
		typedef UINT_PTR ONTIMER_TYPE;
	#else
		typedef UINT ONTIMER_TYPE;
	#endif

#endif

// The number of samples per data series used in this demo
const int sampleSize = 240;

/////////////////////////////////////////////////////////////////////////////
// CRealtimedemoDlg dialog

class CRealtimedemoDlg : public CDialog
{
public:
// Construction
	CRealtimedemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRealtimedemoDlg)
	enum { IDD = IDD_REALTIMEDEMO_DIALOG };
	CStatic	m_ValueC;
	CStatic	m_ValueB;
	CStatic	m_ValueA;
	CChartViewer m_ChartViewer;
	CButton	m_RunPB;
	CSpinButtonCtrl	m_AlarmSpin;
	CComboBox	m_UpdatePeriod;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealtimedemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRealtimedemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(ONTIMER_TYPE nIDEvent);
	afx_msg void OnRunPB();
	afx_msg void OnFreezePB();
	afx_msg void OnSelchangeUpdatePeriod();
	afx_msg void OnDeltaposAlarmSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnViewPortChanged();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	double m_timeStamps[sampleSize];	// The timestamps for the data series
	double m_dataSeriesA[sampleSize];	// The values for the data series A
	double m_dataSeriesB[sampleSize];	// The values for the data series B
	double m_dataSeriesC[sampleSize];	// The values for the data series C

	double m_nextDataTime;	// Used by the random number generator to generate real time data.
	int m_extBgColor;		// The default background color.
	int m_threshold;		// The current alarm threshold

	// Shift new data values into the real time data series 
	void getData();
	
	// Draw chart
	void drawChart(CChartViewer *viewer);

	// utility to get default background color
	int getDefaultBgColor();
	// utility to load icon resource to a button
	void loadButtonIcon(int buttonId, int iconId, int width, int height);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEDEMODLG_H__BE2F0092_7DD2_4D82_991B_4CF30D500281__INCLUDED_)
