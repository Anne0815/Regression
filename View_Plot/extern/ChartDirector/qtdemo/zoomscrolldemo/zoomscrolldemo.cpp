#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QButtonGroup>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include "zoomscrolldemo.h"
#include "hotspotdialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("* {font-family:arial;font-size:11px}");
    ZoomScrollDemo demo;
    demo.show();
    return app.exec();
}


//
// Because QT uses QDateTime, while ChartDirector uses Chart::chartTime, we need
// utilities to convert from one to another
//

// Convert from QDateTime to chartTime
static double QDateTimeToChartTime(QDateTime q)
{
    QDate d = q.date();
    QTime t = q.time();
    return Chart::chartTime(d.year(), d.month(), d.day(), t.hour(), t.minute(),
                            t.second()) + t.msec() / 1000.0;
}

// Convert from chartTime to QDateTime
static QDateTime ChartTimeToQDateTime(double t)
{
    double ymdhms = floor(t);
    int ms = (int)(floor((t - ymdhms) * 1000));
    int ymd = Chart::getChartYMD(ymdhms);
    int hms = (int)fmod(ymdhms, 86400);

    return QDateTime(QDate(ymd / 10000, (ymd % 10000) / 100, ymd % 100),
        QTime(hms / 3600, (hms % 3600) / 60, hms % 60, ms));
}

ZoomScrollDemo::ZoomScrollDemo(QWidget *parent) :
    QDialog(parent)
{
    //
    // Set up the GUI
    //

    setFixedSize(758, 334);
    setWindowTitle("Zooming and Scrolling Demonstration");

    // The frame on the left side
    QFrame *frame = new QFrame(this);
    frame->setGeometry(4, 4, 120, 326);
    frame->setFrameShape(QFrame::StyledPanel);

    // Pointer push button
    QPushButton *pointerPB = new QPushButton(QIcon(":/pointer.png"), "Pointer", frame);
    pointerPB->setGeometry(4, 8, 112, 28);
    pointerPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    pointerPB->setCheckable(true);

    // Zoom In push button
    QPushButton *zoomInPB = new QPushButton(QIcon(":/zoomin.png"), "Zoom In", frame);
    zoomInPB->setGeometry(4, 36, 112, 28);
    zoomInPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    zoomInPB->setCheckable(true);

    // Zoom Out push button
    QPushButton *zoomOutPB = new QPushButton(QIcon(":/zoomout.png"), "Zoom Out", frame);
    zoomOutPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    zoomOutPB->setGeometry(4, 64, 112, 28);
    zoomOutPB->setCheckable(true);

    // The Pointer/Zoom In/Zoom Out buttons form a button group
    QButtonGroup *mouseUsage = new QButtonGroup(frame);
    mouseUsage->addButton(pointerPB, Chart::MouseUsageScroll);
    mouseUsage->addButton(zoomInPB, Chart::MouseUsageZoomIn);
    mouseUsage->addButton(zoomOutPB, Chart::MouseUsageZoomOut);
    connect(mouseUsage, SIGNAL(buttonPressed(int)), SLOT(onMouseUsageChanged(int)));

    // Zoom Mode label
    (new QLabel("Zoom Mode", frame))->setGeometry(6, 104, 112, 18);
    
    // X Zoom push button
    QPushButton *xZoomPB = new QPushButton(QIcon(":/xrange.png"), "X Zoom", frame);
    xZoomPB->setGeometry(4, 122, 112, 28);
    xZoomPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    xZoomPB->setCheckable(true);

    // XY Zoom push button
    QPushButton *xyZoomPB = new QPushButton(QIcon(":/xyrange.png"), "XY Zoom", frame);
    xyZoomPB->setGeometry(4, 150, 112, 28);
    xyZoomPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    xyZoomPB->setCheckable(true);

    // The X Zoom/XY Zoom buttons form a button group
    QButtonGroup *zoomMode = new QButtonGroup(frame);
    zoomMode->addButton(xZoomPB, Chart::DirectionHorizontal);
    zoomMode->addButton(xyZoomPB, Chart::DirectionHorizontalVertical);
    connect(zoomMode, SIGNAL(buttonPressed(int)), SLOT(onZoomModeChanged(int)));

    // Start Date control
    (new QLabel("Start Date", frame))->setGeometry(6, 190, 112, 18);
    m_StartDate = new QDateEdit(frame);
    m_StartDate->setGeometry(4, 208, 113, 22);
    connect(m_StartDate, SIGNAL(dateTimeChanged(QDateTime)), SLOT(onStartDateChanged(QDateTime)));

    // Duration control
    (new QLabel("Duration (Days)", frame))->setGeometry(6, 244, 112, 18);
    m_Duration = new QComboBox(frame);
    m_Duration->setGeometry(4, 262, 113, 22);
    m_Duration->setEditable(true);
    m_Duration->setInsertPolicy(QComboBox::NoInsert);
    m_Duration->addItems(QStringList() << "10" << "20" << "30" << "60" << "90" << "180"
                             << "360" << "720" << "1080" << "1440");
    connect(m_Duration, SIGNAL(editTextChanged(QString)), SLOT(onDurationChanged(QString)));

    // Chart Viewer
    m_ChartViewer = new QChartViewer(this);
    m_ChartViewer->setGeometry(132, 8, 600, 300);
    connect(m_ChartViewer, SIGNAL(viewPortChanged()), SLOT(onViewPortChanged()));
    connect(m_ChartViewer, SIGNAL(mouseMove(QMouseEvent*)), SLOT(onMouseMove(QMouseEvent*)));
    connect(m_ChartViewer, SIGNAL(clicked(QMouseEvent*)), SLOT(onChartClicked(QMouseEvent*)));

    // Horizontal scroll bar
    m_HScrollBar = new QScrollBar(Qt::Horizontal, this);
    m_HScrollBar->setGeometry(132, 316, 608, 17);
    connect(m_HScrollBar, SIGNAL(valueChanged(int)), SLOT(onHScrollBarChanged(int)));

    // Vertical scroll bar
    m_VScrollBar = new QScrollBar(Qt::Vertical, this);
    m_VScrollBar->setGeometry(740, 0, 17, 316);
    connect(m_VScrollBar, SIGNAL(valueChanged(int)), SLOT(onVScrollBarChanged(int)));

    //
    // Initialize member variables
    //

    // y axes ranges
    m_minValue = m_maxValue = 0;

    // Load the data
    loadData();

    //
    // In this demo, we deduce the horizontal scroll range from the data.
    //

    // Earliest date is the first timestamp
    m_minDate = m_timeStamps[0];
    // Duration is the seconds elapsed of the last timestamp from the earliest date
    m_dateRange = m_timeStamps[m_timeStamps.len - 1] - m_minDate;

    // In this demo, the maximum zoom-in is set to 10 days (1 day = 86400 seconds)
    m_minDuration = 10 * 86400;

    // Set up the ChartViewer to reflect the visible and minimum duration
    m_ChartViewer->setZoomInWidthLimit(m_minDuration / m_dateRange);
    m_ChartViewer->setViewPortWidth(m_currentDuration / m_dateRange);
    m_ChartViewer->setViewPortLeft(1 - m_ChartViewer->getViewPortWidth());

    // Initially set the mouse to drag to scroll mode in horizontal direction.
    pointerPB->click();
    xZoomPB->click();
    m_ChartViewer->updateViewPort(true, true);
}

ZoomScrollDemo::~ZoomScrollDemo()
{
    delete m_dataTable;
    delete m_ChartViewer->getChart();
}

//
// The Pointer, Zoom In or Zoom out button is pressed
//
void ZoomScrollDemo::onMouseUsageChanged(int mouseUsage)
{
    m_ChartViewer->setMouseUsage(mouseUsage);
}

//
// The X Zoom or XY Zoom button is pressed
//
void ZoomScrollDemo::onZoomModeChanged(int zoomMode)
{
    m_ChartViewer->setZoomDirection(zoomMode);
    m_ChartViewer->setScrollDirection(zoomMode);

    if (zoomMode == Chart::DirectionHorizontal)
    {
        // Viewport is always unzoomed as y-axis is auto-scaled
        m_ChartViewer->setViewPortTop(0);
        m_ChartViewer->setViewPortHeight(1);

        // Update chart to auto-scale axis
        m_ChartViewer->updateViewPort(true, true);
    }
}

//
// User selects a start date from the QDateEdit control
//
void ZoomScrollDemo::onStartDateChanged(QDateTime date)
{
    // Compute the new view port position based on the selected date
    m_ChartViewer->setViewPortLeft(
        (QDateTimeToChartTime(date) - m_minDate) / m_dateRange);
    m_ChartViewer->updateViewPort(true, true);
}

//
// User selects a duration from the Duration combo box
//
void ZoomScrollDemo::onDurationChanged(QString s)
{
    // Parse the duration text
    double newDuration = s.toDouble() * 86400;
    if (newDuration == 0)
        return;

    // Duration too short or not numeric?
    if (newDuration < m_minDuration)
        newDuration = m_minDuration;

    if (newDuration != m_currentDuration)
    {
        // Set the ViewPortWidth according to the new duration
        m_currentDuration = newDuration;
        m_ChartViewer->setViewPortWidth(newDuration / m_dateRange);

        // Update the chart
        m_ChartViewer->updateViewPort(true, true);
    }
}

//
// User clicks on the the horizontal scroll bar
//
void ZoomScrollDemo::onHScrollBarChanged(int value)
{
    // Set the view port based on the scroll bar
    int scrollBarLen = m_HScrollBar->maximum() + m_HScrollBar->pageStep();
    m_ChartViewer->setViewPortLeft(value / (double)scrollBarLen);

    // Update the chart display without updating the image maps. (We can delay updating
    // the image map until scrolling is completed and the chart display is stable.)
    m_ChartViewer->updateViewPort(true, false);
}

//
// User clicks on the the vertical scroll bar
//
void ZoomScrollDemo::onVScrollBarChanged(int value)
{
    // Set the view port based on the scroll bar
    int scrollBarLen = m_VScrollBar->maximum() + m_VScrollBar->pageStep();
    m_ChartViewer->setViewPortTop(value / (double)scrollBarLen);

    // Update the chart display without updating the image maps. (We can delay updating
    // the image map until scrolling is completed and the chart display is stable.)
    m_ChartViewer->updateViewPort(true, false);
}

//
// QChartViewer ViewPortChanged event
//
void ZoomScrollDemo::onViewPortChanged()
{
    QChartViewer *viewer = (QChartViewer *)QObject::sender();

    // Update other controls in the user interface
    updateControls(viewer);

    //
    // Update chart and image map if necessary
    //
    if (viewer->needUpdateChart())
        drawChart(viewer);
    if (viewer->needUpdateImageMap())
        updateImageMap(viewer);
}

//
// Update controls in the user interface when the view port changed
//
void ZoomScrollDemo::updateControls(QChartViewer *viewer)
{
    //
    // Update the scroll bars to reflect the view port setting
    //

    // The logical length of the scrollbar. It can be any large value. The actual value does
    // not matter.
    const int scrollBarLen = 1000000000;

    // Update the horizontal scroll bar
    m_HScrollBar->setEnabled(viewer->getViewPortWidth() < 1);
    m_HScrollBar->setPageStep((int)ceil(viewer->getViewPortWidth() * scrollBarLen));
    m_HScrollBar->setRange(0, scrollBarLen - m_HScrollBar->pageStep());
    m_HScrollBar->setValue((int)(0.5 + viewer->getViewPortLeft() * scrollBarLen));

    // Update the vertical scroll bar
    m_VScrollBar->setEnabled(viewer->getViewPortHeight() < 1);
    m_VScrollBar->setPageStep((int)ceil(viewer->getViewPortHeight() * scrollBarLen));
    m_VScrollBar->setRange(0, scrollBarLen - m_VScrollBar->pageStep());
    m_VScrollBar->setValue((int)(0.5 + viewer->getViewPortTop() * scrollBarLen));

    //
    // Update the start date in the QDataEdit control.
    //
    double currentStartDate = m_minDate + (int)(0.5 + viewer->getViewPortLeft()
        * m_dateRange);
    m_StartDate->setDateTimeRange(ChartTimeToQDateTime(m_minDate),
                                  ChartTimeToQDateTime(m_minDate + m_dateRange));
    m_StartDate->setDateTime(ChartTimeToQDateTime(currentStartDate));

    //
    // Update the duration in the QComboBox
    //
    m_currentDuration = (int)(0.5 + viewer->getViewPortWidth() * m_dateRange);
    m_Duration->lineEdit()->setText(QString("%1").arg((int)(0.5 + m_currentDuration / 86400)));
}

//
// User clicks on the QChartViewer
//
void ZoomScrollDemo::onChartClicked(QMouseEvent *)
{
    QChartViewer *viewer = (QChartViewer *)QObject::sender();
    ImageMapHandler *handler = viewer->getImageMapHandler();
    if (0 != handler)
    {
        // Query the ImageMapHandler to see if the mouse is on a clickable hot spot. We
        // consider the hot spot as clickable if its href ("path") parameter is not empty.
        const char *path = handler->getValue("path");
        if ((0 != path) && (0 != *path))
        {
            // In this sample code, we just show all hot spot parameters.
            HotSpotDialog hs;
            hs.setData(handler);
            hs.exec();
        }
    }
}

//
// Load the data
//
void ZoomScrollDemo::loadData()
{
    // In this demo, we allow scrolling for the last 5 years.
    QDateTime t = QDateTime::currentDateTime();
    double lastDate = QDateTimeToChartTime(t);
    double firstDate = QDateTimeToChartTime(t.addYears(-5));

    // The initial view port is to show 1 year of data.
    m_currentDuration = lastDate - QDateTimeToChartTime(t.addYears(-1));

    //
    // Get the data and stores them in a memory buffer for fast scrolling / zooming. In
    // this demo, we just use a random number generator. In practice, you may get the data
    // from a database or XML or by other means.
    //

    // Set up random number generator
    m_dataTable = new RanTable(127, 4, (int)((lastDate - firstDate) / 86400) + 1);
    m_dataTable->setDateCol(0, firstDate, 86400);
    m_dataTable->setCol(1, 150, -10, 10);
    m_dataTable->setCol(2, 200, -10, 10);
    m_dataTable->setCol(3, 250, -10, 10);

    // Read random data into the data arrays
    m_timeStamps = m_dataTable->getCol(0);
    m_dataSeriesA = m_dataTable->getCol(1);
    m_dataSeriesB = m_dataTable->getCol(2);
    m_dataSeriesC = m_dataTable->getCol(3);
}

//
// Draw the chart and display it in the given viewer
//
void ZoomScrollDemo::drawChart(QChartViewer *viewer)
{
    //
    // In this demo, we copy the visible part of the data to a separate buffer for chart
    // plotting.
    //
    // Note that if you only have a small amount of data (a few hundred data points), it
    // may be easier to just plot all data in any case (so the following copying code is
    // not needed), and let ChartDirector "clip" the chart to the plot area.
    //

    // Using ViewPortLeft and ViewPortWidth, get the start and end dates of the view port.
    double viewPortStartDate = m_minDate + floor(viewer->getViewPortLeft() *
        m_dateRange + 0.5);
    double viewPortEndDate = viewPortStartDate + floor(viewer->getViewPortWidth() *
        m_dateRange + 0.5);

    // Get the starting index of the array using the start date
    int startIndex = (int)(std::lower_bound(m_timeStamps.data, m_timeStamps.data + m_timeStamps.len,
        viewPortStartDate) - m_timeStamps.data);
    if ((startIndex > 0) && (m_timeStamps[startIndex] != viewPortStartDate))
        --startIndex;

    // Get the ending index of the array using the end date
    int endIndex = (int)(std::upper_bound(m_timeStamps.data, m_timeStamps.data + m_timeStamps.len,
        viewPortEndDate) - m_timeStamps.data);
        if (endIndex >= m_timeStamps.len - 1)
                endIndex = m_timeStamps.len - 1;

    // Get the length
    int noOfPoints = endIndex - startIndex + 1;

    // We copy the visible data from the main arrays to separate data arrays
    double* viewPortTimeStamps = new double[noOfPoints];
    double* viewPortDataSeriesA = new double[noOfPoints];
    double* viewPortDataSeriesB = new double[noOfPoints];
    double* viewPortDataSeriesC = new double[noOfPoints];
    int arraySizeInBytes = noOfPoints * sizeof(double);
    memcpy(viewPortTimeStamps, m_timeStamps.data + startIndex, arraySizeInBytes);
    memcpy(viewPortDataSeriesA, m_dataSeriesA.data + startIndex, arraySizeInBytes);
    memcpy(viewPortDataSeriesB, m_dataSeriesB.data + startIndex, arraySizeInBytes);
    memcpy(viewPortDataSeriesC, m_dataSeriesC.data + startIndex, arraySizeInBytes);

    if (noOfPoints >= 520)
    {
        //
        // Zoomable chart with high zooming ratios often need to plot many thousands of
        // points when fully zoomed out. However, it is usually not needed to plot more
        // data points than the resolution of the chart. Plotting too many points may cause
        // the points and the lines to overlap. So rather than increasing resolution, this
        // reduces the clarity of the chart. So it is better to aggregate the data first if
        // there are too many points.
        //
        // In our current example, the chart only has 520 pixels in width and is using a 2
        // pixel line width. So if there are more than 520 data points, we aggregate the
        // data using the ChartDirector aggregation utility method.
        //
        // If in your real application, you do not have too many data points, you may
        // remove the following code altogether.
        //

        // Set up an aggregator to aggregate the data based on regular sized slots
        ArrayMath m(DoubleArray(viewPortTimeStamps, noOfPoints));
        m.selectRegularSpacing(noOfPoints / 260);

        // For the timestamps, take the first timestamp on each slot
        int aggregatedNoOfPoints = m.aggregate(DoubleArray(viewPortTimeStamps, noOfPoints),
            Chart::AggregateFirst).len;

        // For the data values, aggregate by taking the averages
        m.aggregate(DoubleArray(viewPortDataSeriesA, noOfPoints), Chart::AggregateAvg);
        m.aggregate(DoubleArray(viewPortDataSeriesB, noOfPoints), Chart::AggregateAvg);
        m.aggregate(DoubleArray(viewPortDataSeriesC, noOfPoints), Chart::AggregateAvg);

        noOfPoints = aggregatedNoOfPoints;
    }

    //
    // Now we have obtained the data, we can plot the chart.
    //

    ///////////////////////////////////////////////////////////////////////////////////////
    // Step 1 - Configure overall chart appearance.
    ///////////////////////////////////////////////////////////////////////////////////////

    // Create an XYChart object 600 x 300 pixels in size, with pale blue (0xf0f0ff)
    // background, black (000000) border, 1 pixel raised effect, and with a rounded frame.
    XYChart *c = new XYChart(600, 300, 0xf0f0ff, 0, 1);
    QColor bgColor = palette().color(backgroundRole()).rgb();
    c->setRoundedFrame((bgColor.red() << 16) + (bgColor.green() << 8) + bgColor.blue());

    // Set the plotarea at (52, 60) and of size 520 x 192 pixels. Use white (ffffff)
    // background. Enable both horizontal and vertical grids by setting their colors to
    // grey (cccccc). Set clipping mode to clip the data lines to the plot area.
    c->setPlotArea(52, 60, 520, 192, 0xffffff, -1, -1, 0xcccccc, 0xcccccc);
    c->setClipping();

    // Add a top title to the chart using 15 pts Times New Roman Bold Italic font, with a
    // light blue (ccccff) background, black (000000) border, and a glass like raised effect.
    c->addTitle("Zooming and Scrolling Demonstration", "timesbi.ttf", 15
        )->setBackground(0xccccff, 0x0, Chart::glassEffect());

    // Add a bottom title to the chart to show the date range of the axis, with a light blue
    // (ccccff) background.
    char formattedStartDate[32];
    char formattedEndDate[32];
    strcpy(formattedStartDate, c->formatValue(viewPortStartDate, "{value|mmm dd, yyyy}"));
    strcpy(formattedEndDate, c->formatValue(viewPortEndDate, "{value|mmm dd, yyyy}"));
    char buffer[2048];
    sprintf(buffer, "From <*font=arialbi.ttf*>%s<*/font*> to <*font=arialbi.ttf*>%s<*/font*>"
        " (Duration <*font=arialbi.ttf*>%d<*/font*> days)", formattedStartDate,
        formattedEndDate, (int)((viewPortEndDate - viewPortStartDate) / 86400.0 + 0.5));
    c->addTitle(Chart::Bottom, buffer, "ariali.ttf", 10)->setBackground(0xccccff);

    // Add a legend box at the top of the plot area with 9pts Arial Bold font with flow layout.
    c->addLegend(50, 33, false, "arialbd.ttf", 9)->setBackground(Chart::Transparent,
        Chart::Transparent);

    // Set axes width to 2 pixels
    c->yAxis()->setWidth(2);
    c->xAxis()->setWidth(2);

    // Add a title to the y-axis
    c->yAxis()->setTitle("Price (USD)", "arialbd.ttf", 9);

    ///////////////////////////////////////////////////////////////////////////////////////
    // Step 2 - Add data to chart
    ///////////////////////////////////////////////////////////////////////////////////////

    //
    // In this example, we represent the data by lines. You may modify the code below if
    // you want to use other representations (areas, scatter plot, etc).
    //

    // Add a line layer for the lines, using a line width of 2 pixels
    Layer *layer = c->addLineLayer();
    layer->setLineWidth(2);

    // Now we add the 3 data series to a line layer, using the color red (ff0000), green
    // (00cc00) and blue (0000ff)
    layer->setXData(DoubleArray(viewPortTimeStamps, noOfPoints));
    layer->addDataSet(DoubleArray(viewPortDataSeriesA, noOfPoints), 0xff0000, "Product Alpha");
    layer->addDataSet(DoubleArray(viewPortDataSeriesB, noOfPoints), 0x00cc00, "Product Beta");
    layer->addDataSet(DoubleArray(viewPortDataSeriesC, noOfPoints), 0x0000ff, "Product Gamma");

    ///////////////////////////////////////////////////////////////////////////////////////
    // Step 3 - Set up x-axis scale
    ///////////////////////////////////////////////////////////////////////////////////////

    // Set x-axis date scale to the view port date range.
    c->xAxis()->setDateScale(viewPortStartDate, viewPortEndDate);

    //
    // In the current demo, the x-axis range can be from a few years to a few days. We can
    // let ChartDirector auto-determine the date/time format. However, for more beautiful
    // formatting, we set up several label formats to be applied at different conditions.
    //

    // If all ticks are yearly aligned, then we use "yyyy" as the label format.
    c->xAxis()->setFormatCondition("align", 360 * 86400);
    c->xAxis()->setLabelFormat("{value|yyyy}");

    // If all ticks are monthly aligned, then we use "mmm yyyy" in bold font as the first
    // label of a year, and "mmm" for other labels.
    c->xAxis()->setFormatCondition("align", 30 * 86400);
    c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), "<*font=bold*>{value|mmm yyyy}",
        Chart::AllPassFilter(), "{value|mmm}");

    // If all ticks are daily algined, then we use "mmm dd<*br*>yyyy" in bold font as the
    // first label of a year, and "mmm dd" in bold font as the first label of a month, and
    // "dd" for other labels.
    c->xAxis()->setFormatCondition("align", 86400);
    c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(),
        "<*block,halign=left*><*font=bold*>{value|mmm dd<*br*>yyyy}",
        Chart::StartOfMonthFilter(), "<*font=bold*>{value|mmm dd}");
    c->xAxis()->setMultiFormat(Chart::AllPassFilter(), "{value|dd}");

    // For all other cases (sub-daily ticks), use "hh:nn<*br*>mmm dd" for the first label of
    // a day, and "hh:nn" for other labels.
    c->xAxis()->setFormatCondition("else");
    c->xAxis()->setMultiFormat(Chart::StartOfDayFilter(),
        "<*font=bold*>{value|hh:nn<*br*>mmm dd}", Chart::AllPassFilter(), "{value|hh:nn}");

    ///////////////////////////////////////////////////////////////////////////////////////
    // Step 4 - Set up y-axis scale
    ///////////////////////////////////////////////////////////////////////////////////////

    if ((viewer->getZoomDirection() == Chart::DirectionHorizontal) ||
        ((m_minValue == 0) && (m_maxValue == 0)))
    {
        // y-axis is auto-scaled - save the chosen y-axis scaled to support xy-zoom mode
        c->layout();
        m_minValue = c->yAxis()->getMinValue();
        m_maxValue = c->yAxis()->getMaxValue();
    }
    else
    {
        // xy-zoom mode - compute the actual axis scale in the view port
        double axisLowerLimit =  m_maxValue - (m_maxValue - m_minValue) *
            (viewer->getViewPortTop() + viewer->getViewPortHeight());
        double axisUpperLimit =  m_maxValue - (m_maxValue - m_minValue) *
            viewer->getViewPortTop();
        // *** use the following formula if you are using a log scale axis ***
        // double axisLowerLimit = m_maxValue * pow(m_minValue / m_maxValue,
        //  viewer->getViewPortTop() + viewer->getViewPortHeight());
        // double axisUpperLimit = m_maxValue * pow(m_minValue / m_maxValue,
        //  viewer->getViewPortTop());

        // use the zoomed-in scale
        c->yAxis()->setLinearScale(axisLowerLimit, axisUpperLimit);
        c->yAxis()->setRounding(false, false);
    }

    ///////////////////////////////////////////////////////////////////////////////////////
    // Step 5 - Display the chart
    ///////////////////////////////////////////////////////////////////////////////////////

    // Set the chart image to the WinChartViewer
    delete viewer->getChart();
    viewer->setChart(c);

    // Free resources
    delete[] viewPortTimeStamps;
    delete[] viewPortDataSeriesA;
    delete[] viewPortDataSeriesB;
    delete[] viewPortDataSeriesC;
}

//
// Update the image map
//
void ZoomScrollDemo::updateImageMap(QChartViewer *viewer)
{
    if (0 == viewer->getImageMapHandler())
    {
        // no existing image map - creates a new one
        viewer->setImageMap(viewer->getChart()->getHTMLImageMap("clickable", "",
                "title='[{dataSetName}] {x|mmm dd, yyyy}: USD {value|2}'"));
    }
}

//
// When the mouse enters the chart, we will generate an image map for hot spots and tooltips
// support if it has not already been generated.
//
void ZoomScrollDemo::onMouseMove(QMouseEvent *)
{
    updateImageMap((QChartViewer *)QObject::sender());
}
