////////////////////////////////////////////////////////////////////////////
// Handles the main view of this sample application.
////////////////////////////////////////////////////////////////////////////

// mfcdemoView.cpp : implementation of the CMfcdemoView class
//

#include "stdafx.h"
#include "mfcdemo.h"
#include "mfcdemoDoc.h"
#include "mfcdemoView.h"
#include "mfcCharts.h"
#include "HotSpotDlg.h"
#include "chartdir.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcdemoView

IMPLEMENT_DYNCREATE(CMfcdemoView, CFormView)

BEGIN_MESSAGE_MAP(CMfcdemoView, CFormView)
	//{{AFX_MSG_MAP(CMfcdemoView)
	ON_LBN_SELCHANGE(IDC_CHART_LIST, OnSelchangeChartList)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHARTVIEWER0, IDC_CHARTVIEWER7, CMfcdemoView::OnChartClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcdemoView construction

//
// Constructor
//
CMfcdemoView::CMfcdemoView()
	: CFormView(CMfcdemoView::IDD)
{
	//{{AFX_DATA_INIT(CMfcdemoView)
	//}}AFX_DATA_INIT

	// This demo view is capable of displaying 8 chart images at the same 
	// time. We store the m_ChartViewer in an array to facilitate processing
	// using loops
	m_ChartViewer[0] = &m_ChartViewer0;
	m_ChartViewer[1] = &m_ChartViewer1;
	m_ChartViewer[2] = &m_ChartViewer2;
	m_ChartViewer[3] = &m_ChartViewer3;
	m_ChartViewer[4] = &m_ChartViewer4;
	m_ChartViewer[5] = &m_ChartViewer5;
	m_ChartViewer[6] = &m_ChartViewer6;
	m_ChartViewer[7] = &m_ChartViewer7;
}

void CMfcdemoView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfcdemoView)
	DDX_Control(pDX, IDC_CHARTVIEWER7, m_ChartViewer7);
	DDX_Control(pDX, IDC_CHARTVIEWER6, m_ChartViewer6);
	DDX_Control(pDX, IDC_CHARTVIEWER5, m_ChartViewer5);
	DDX_Control(pDX, IDC_CHARTVIEWER4, m_ChartViewer4);
	DDX_Control(pDX, IDC_CHARTVIEWER3, m_ChartViewer3);
	DDX_Control(pDX, IDC_CHARTVIEWER2, m_ChartViewer2);
	DDX_Control(pDX, IDC_CHARTVIEWER1, m_ChartViewer1);
	DDX_Control(pDX, IDC_CHARTVIEWER0, m_ChartViewer0);
	DDX_Control(pDX, IDC_CHART_LIST, m_ChartList);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CMfcdemoView printing

BOOL CMfcdemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMfcdemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMfcdemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMfcdemoView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CMfcdemoView diagnostics

#ifdef _DEBUG
void CMfcdemoView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMfcdemoView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMfcdemoDoc* CMfcdemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcdemoDoc)));
	return (CMfcdemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcdemoView message handlers

//
// Initialization
//
void CMfcdemoView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// Initialize the demo chart selection list
	m_ChartList.ResetContent();
	for (DemoChart *d = demoCharts; d->name != 0; ++d)
		// The CString below is to handle possible conversion between const char *
		// and TCHAR in case the MFC is configured to compile in Unicode
		m_ChartList.AddString(CString(d->name));

	// To keep this program simple, we disable windows scrolling.
	SetScrollSizes(MM_TEXT, CSize(0, 0));
	GetParentFrame()->CenterWindow(); 
}

//
// Handle the ON_WM_ERASEBKGND message to set background color
//
BOOL CMfcdemoView::OnEraseBkgnd(CDC* pDC) 
{ 
	// Set brush to desired background color 
	CBrush backBrush(RGB(255, 255, 255)); 

	// Save old brush 
	CBrush* pOldBrush = pDC->SelectObject(&backBrush); 

	// Erase the area needed with the given background color
	CRect rect; 
	pDC->GetClipBox(&rect);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY); 

	// Restore old brush and exit
	pDC->SelectObject(pOldBrush); 
	return TRUE; 
} 

//
// Handles user selection from the listbox control
//
void CMfcdemoView::OnSelchangeChartList() 
{
	// Get the demo chart function based on the list box selection
	DemoChart demoChart = demoCharts[m_ChartList.GetCurSel()];
	if (demoChart.noOfCharts == 0)
		return; // Just a separator line - not a real demo chart

	// Hide and clear the old charts
	int i;
	for (i = 0; i < 8; ++i)
	{
		m_ChartViewer[i]->ShowWindow(FALSE);
		m_ChartViewer[i]->setChart(0);
	}

	// Create the demo charts
	for (i = 0; i < demoChart.noOfCharts; ++i)
	{
		// Get the chart and the image map
		const char *imageMap = 0;
		BaseChart *c = demoChart.createChart(i, &imageMap);
			
		// Set the chart and the image map
		m_ChartViewer[i]->setChart(c);
		m_ChartViewer[i]->setImageMap(imageMap);
	
		// Can free the demo chart now after setting everything to the control
		delete c;
	}
	
	// Flow layout the charts on the screen
	layoutCharts();
}

//
// Handles resize event
//
void CMfcdemoView::OnSize(UINT nType, int cx, int cy) 
{
	if (m_ChartList.m_hWnd != 0)
	{
		// Resize the list box to fit the window size
		CRect rect;
		m_ChartList.GetWindowRect(&rect);
		m_ChartList.MoveWindow(0, 0, rect.right - rect.left, cy - 0);

		// Re-layout the charts when window size changes
		layoutCharts();
 	}

	CFormView::OnSize(nType, cx, cy);
}

//
// Handles mouse clicks on the chart image
//
void CMfcdemoView::OnChartClick(UINT nID)
{
	// In this demo program, all ChartViewers are handled by this handler. We need to 
	// retrieve the ChartViewer that generates the message and get its ImageMapHandler.
	int chartViewerIndex = nID - IDC_CHARTVIEWER0;
	ImageMapHandler *handler = m_ChartViewer[chartViewerIndex]->getImageMapHandler();
	
	if (0 != handler)
	{
		// Query the ImageMapHandler to see if the mouse is on a clickable hot spot. We 
		// consider the hot spot as clickable if its href ("path") parameter is not empty.
		const char *path = handler->getValue("path");
		if ((0 != path) && (0 != *path))
		{
			// In this sample code, we just show all hot spot parameters.
			CHotSpotDlg hs;
			hs.SetData(handler);
			hs.DoModal();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMfcdemoView methods

//
// Flow layout the charts
//
void CMfcdemoView::layoutCharts()
{
	// Get the size of the window
	CRect winRect;
	GetWindowRect(&winRect);

	// Get the size and position of the list box
	CRect listRect;
	m_ChartList.GetWindowRect(&listRect);

	// The margin between charts. 
	int margin = 5;

	// The first chart is at the right side of the list box.
	int cursorX = listRect.right - winRect.left + margin;

	// The first chart is align with the top of the list box.
	int cursorY = listRect.top - winRect.top + margin;
	
	int maxWidth = 0;
	int lineHeight = 0;

	int i;
	for (i = 0; i < 8; ++i)
	{
		if (m_ChartViewer[i]->GetBitmap() == 0)
			break;	// No more charts, can break now
	
		// Get the size of the chart
		CRect chartRect;
		m_ChartViewer[i]->GetWindowRect(&chartRect);

		if ((i > 0) && (cursorX + (chartRect.right - chartRect.left) > 
			(winRect.right - winRect.left)))
		{
			// There is not enough space left for the chart, so move to next line
			cursorY += (lineHeight + margin);
			cursorX = listRect.right - winRect.left + margin;
			lineHeight = 0;
		}

		// Put the chart in the current cursor position
		m_ChartViewer[i]->MoveWindow(cursorX, cursorY, chartRect.right - chartRect.left,
			chartRect.bottom - chartRect.top);
		
		// Advance the x cursor
		cursorX += (chartRect.right - chartRect.left + margin);
		
		// Update the maximum line width
		if (cursorX > maxWidth)
			maxWidth = cursorX;
		
		// Update the line height
		if (chartRect.bottom - chartRect.top > lineHeight)
			lineHeight = chartRect.bottom - chartRect.top;
	}

	// Show the charts
	for (i = 0; i < 8; ++i)
		m_ChartViewer[i]->ShowWindow(TRUE);
}

