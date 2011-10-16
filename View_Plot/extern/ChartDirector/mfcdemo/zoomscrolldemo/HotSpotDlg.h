#if !defined(AFX_HOTSPOTDLG_H__B47C5CD5_B465_4363_9772_2438D3AB3EC9__INCLUDED_)
#define AFX_HOTSPOTDLG_H__B47C5CD5_B465_4363_9772_2438D3AB3EC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HotSpotDlg.h : header file
//

// Forward declarations
class ImageMapHandler;


/////////////////////////////////////////////////////////////////////////////
// CHotSpotDlg dialog

class CHotSpotDlg : public CDialog
{
public:
// Construction
	CHotSpotDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHotSpotDlg)
	enum { IDD = IDD_HOTSPOTPARAM };
	CListCtrl	m_ParamList;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHotSpotDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	protected:
	virtual BOOL OnInitDialog();

// Implementation
	public:
	virtual void SetData(ImageMapHandler *data);

// Member Variables
	private:
	ImageMapHandler *hotSpotData;

protected:

	// Generated message map functions
	//{{AFX_MSG(CHotSpotDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOTSPOTDLG_H__B47C5CD5_B465_4363_9772_2438D3AB3EC9__INCLUDED_)
