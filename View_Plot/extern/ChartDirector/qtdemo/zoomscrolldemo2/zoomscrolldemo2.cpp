#include <QApplication>
#include <QGridLayout>
#include <QButtonGroup>
#include "zoomscrolldemo2.h"
#include "hotspotdialog.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyleSheet("* {font-family:arial;font-size:11px}");
    ZoomScrollDemo2 demo;
    demo.show();
    return app.exec();
}


ZoomScrollDemo2::ZoomScrollDemo2(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Zooming and Scrolling Demonstration (2)");
    setFixedSize(644, 488);

    QFrame *frame = new QFrame(this);
    frame->setGeometry(4, 4, 120, 481);
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
    zoomOutPB->setGeometry(4, 64, 112, 28);
    zoomOutPB->setStyleSheet("QPushButton { text-align:left; padding:5px}");
    zoomOutPB->setCheckable(true);

    // The Pointer/Zoom In/Zoom Out buttons form a button group
    QButtonGroup *mouseUsage = new QButtonGroup(frame);
    mouseUsage->addButton(pointerPB, Chart::MouseUsageScroll);
    mouseUsage->addButton(zoomInPB, Chart::MouseUsageZoomIn);
    mouseUsage->addButton(zoomOutPB, Chart::MouseUsageZoomOut);
    connect(mouseUsage, SIGNAL(buttonPressed(int)), SLOT(onMouseUsageChanged(int)));

    // Grid layout to hold the navigate push buttons
    QGridLayout *grid = new QGridLayout(new QWidget(frame));
    grid->parentWidget()->setGeometry(4, 116, 112, 112);
    grid->setSpacing(0);
    grid->setContentsMargins(0, 0, 0, 0);

    // Up-Left push button
    m_UpLeftPB = new QPushButton(QIcon(":/upleftarrow.ico"), "");
    grid->addWidget(m_UpLeftPB, 0, 0);

    // Up push button
    m_UpPB = new QPushButton(QIcon(":/uparrow.ico"), "");
    grid->addWidget(m_UpPB, 0, 1);

    // Up-Right push button
    m_UpRightPB = new QPushButton(QIcon(":/uprightarrow.ico"), "");
    grid->addWidget(m_UpRightPB, 0, 2);

    // Left push button
    m_LeftPB = new QPushButton(QIcon(":/rightarrow.ico"), "");
    grid->addWidget(m_LeftPB, 1, 2);

    // Center push button
    m_CenterPB = new QPushButton(QIcon(":/dot.ico"), "");
    grid->addWidget(m_CenterPB, 1, 1);

    // Right push button
    m_RightPB = new QPushButton(QIcon(":/leftarrow.ico"), "");
    grid->addWidget(m_RightPB, 1, 0);

    // Down-Left push button
    m_DownLeftPB = new QPushButton(QIcon(":/downleftarrow.ico"), "");
    grid->addWidget(m_DownLeftPB, 2, 0);

    // Down push button
    m_DownPB = new QPushButton(QIcon(":/downarrow.ico"), "");
    grid->addWidget(m_DownPB, 2, 1);

    // Down-Right push button
    m_DownRightPB = new QPushButton(QIcon(":/downrightarrow.ico"), "");
    grid->addWidget(m_DownRightPB, 2, 2);

    // All navigate buttons will expand to fill the cells, and connect to the onMovePB slot
    for (int i = 0; i < grid->count(); ++i)
    {
        grid->itemAt(i)->widget()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(grid->itemAt(i)->widget(), SIGNAL(pressed()), SLOT(onMovePB()));
    }

    // Timer to repeat the navigate button signal if the user presses and holds a button
    m_RepeatButtonTimer = new QTimer(this);
    m_RepeatButtonTimer->setInterval(100);
    m_RepeatButtonTimer->setSingleShot(true);
    connect(m_RepeatButtonTimer, SIGNAL(timeout()), SLOT(onMovePB()));

    // Zoom Mode label
    QLabel *zoomModeLabel = new QLabel("Zoom Level", frame);
    zoomModeLabel->setGeometry(6, 250, 110, 18);
    zoomModeLabel->setAlignment(Qt::AlignHCenter);

    // Zoom level bar
    m_ZoomBar = new QSlider(Qt::Horizontal, frame);
    m_ZoomBar->setGeometry(12, 275, 102, 41);
    m_ZoomBar->setRange(1, 100);
    m_ZoomBar->setTickPosition(QSlider::TicksBothSides);
    connect(m_ZoomBar, SIGNAL(valueChanged(int)), SLOT(onZoomBarChanged(int)));

    // The container of the draggable navigation window
    m_NavigatePad = new QFrame(frame);
    m_NavigatePad->setGeometry(4, 364, 113, 113);
    m_NavigatePad->setFrameShape(QFrame::Panel);
    m_NavigatePad->setFrameShadow(QFrame::Sunken);

    // The dragging navigation window
    m_NavigateWindow = new QDragRect(m_NavigatePad);
    m_NavigateWindow->setGeometry(24, 28, 61, 53);
    m_NavigateWindow->setAutoFillBackground(true);
    m_NavigateWindow->setPalette(QPalette(QColor(0xc0, 0xc0, 0xff)));
    m_NavigateWindow->setFrameShape(QFrame::Box);
    m_NavigateWindow->setFrameShadow(QFrame::Plain);
    connect(m_NavigateWindow, SIGNAL(mouseDrag(QPoint, QPoint)),
            SLOT(onNavigateWindowDrag(QPoint, QPoint)));

    // Chart Viewer
    m_ChartViewer = new QChartViewer(this);
    m_ChartViewer->setGeometry(QRect(136, 4, 500, 480));
    connect(m_ChartViewer, SIGNAL(viewPortChanged()), SLOT(onViewPortChanged()));
    connect(m_ChartViewer, SIGNAL(mouseMove(QMouseEvent*)), SLOT(onMouseMove(QMouseEvent*)));
    connect(m_ChartViewer, SIGNAL(clicked(QMouseEvent*)), SLOT(onChartClicked(QMouseEvent*)));

    //
    // Initialize member variables
    //

    // x and y axes ranges
    m_minX = m_maxX = m_minY = m_maxY = 0;

    // Set initial zoom/scroll direction
    m_ChartViewer->setScrollDirection(Chart::DirectionHorizontalVertical);
    m_ChartViewer->setZoomDirection(Chart::DirectionHorizontalVertical);

    // Initially set the mouse to drag to scroll mode
    pointerPB->click();

    // Can update chart now
    m_ChartViewer->updateViewPort(true, true);
}

ZoomScrollDemo2::~ZoomScrollDemo2()
{
    delete m_ChartViewer->getChart();
}

//
// The Pointer, Zoom In or Zoom out button is pressed
//
void ZoomScrollDemo2::onMouseUsageChanged(int mouseUsage)
{
    m_ChartViewer->setMouseUsage(mouseUsage);
}

//
// User moves the Zoom slider control
//
void ZoomScrollDemo2::onZoomBarChanged(int value)
{
     // Remember the center point
     double centerX = m_ChartViewer->getViewPortLeft() +
         m_ChartViewer->getViewPortWidth() / 2;
     double centerY = m_ChartViewer->getViewPortTop() +
         m_ChartViewer->getViewPortHeight() / 2;

     // Aspect ratio and zoom factor
     double aspectRatio = m_ChartViewer->getViewPortWidth() /
         m_ChartViewer->getViewPortHeight();
     double zoomTo = ((double)value) / m_ZoomBar->maximum();

     // Zoom by adjusting ViewPortWidth and ViewPortHeight while maintaining the aspect ratio
     m_ChartViewer->setViewPortWidth(zoomTo * ((aspectRatio < 1) ? 1 : aspectRatio));
     m_ChartViewer->setViewPortHeight(zoomTo * ((aspectRatio > 1) ? 1 : (1 / aspectRatio)));

     // Adjust ViewPortLeft and ViewPortTop to keep center point unchanged
     m_ChartViewer->setViewPortLeft(centerX - m_ChartViewer->getViewPortWidth() / 2);
     m_ChartViewer->setViewPortTop(centerY - m_ChartViewer->getViewPortHeight() / 2);

     // Update the chart image only, but no need to update the image map.
     m_ChartViewer->updateViewPort(true, false);
}

//
// Scroll the chart when the user presses the navigate button
//
void ZoomScrollDemo2::onMovePB()
{
    double deltaX = 0;
    double deltaY = 0;

    if (m_UpPB->isDown() || m_UpLeftPB->isDown() || m_UpRightPB->isDown())
        deltaY = -0.1;
    if (m_DownPB->isDown() || m_DownLeftPB->isDown() || m_DownRightPB->isDown())
        deltaY = 0.1;
    if (m_UpLeftPB->isDown() || m_LeftPB->isDown() || m_DownLeftPB->isDown())
        deltaX = -0.1;
    if (m_UpRightPB->isDown() || m_RightPB->isDown() || m_DownRightPB->isDown())
        deltaX = 0.1;

    if ((deltaX != 0) || (deltaY != 0))
    {
        // Scroll the view port by the specified ratio
        double viewPortLeft = m_ChartViewer->getViewPortLeft() + deltaX *
            m_ChartViewer->getViewPortWidth();
        double viewPortTop = m_ChartViewer->getViewPortTop() + deltaY *
            m_ChartViewer->getViewPortHeight();

        scrollChartTo(viewPortLeft, viewPortTop);

        m_RepeatButtonTimer->stop();
        m_RepeatButtonTimer->start();
    }
    else if (m_CenterPB->isDown())
    {
        // Center button
        double viewPortLeft = 0.5 - m_ChartViewer->getViewPortWidth() / 2;
        double viewPortTop = 0.5 - m_ChartViewer->getViewPortHeight() / 2;

        scrollChartTo(viewPortLeft, viewPortTop);
    }
}

//
// Scroll the chart when the user drags the navigate window
//
void ZoomScrollDemo2::onNavigateWindowDrag(QPoint fromPoint, QPoint toPoint)
{
    //
    // Get the position of the navigate window inside the navigate pad as a ratio between 0 - 1.
    //
    double viewPortLeft = ((double)m_NavigateWindow->x() + toPoint.x() - fromPoint.x() -
        m_NavigatePad->frameWidth()) / (m_NavigatePad->width() - m_NavigatePad->frameWidth() * 2);
    double viewPortTop = ((double)m_NavigateWindow->y() + toPoint.y() - fromPoint.y() -
        m_NavigatePad->frameWidth()) / (m_NavigatePad->height() - m_NavigatePad->frameWidth() * 2);

    scrollChartTo(viewPortLeft, viewPortTop);
}

//
// Scroll the view port to the given position if necessary
//
void ZoomScrollDemo2::scrollChartTo(double viewPortLeft, double viewPortTop)
{
    //
    // Ensures the view port is within valid range.
    //
    if (viewPortLeft < 0)
        viewPortLeft = 0;
    if (viewPortLeft > 1 - m_ChartViewer->getViewPortWidth())
        viewPortLeft = 1 - m_ChartViewer->getViewPortWidth();
    if (viewPortTop < 0)
        viewPortTop = 0;
    if (viewPortTop > 1 - m_ChartViewer->getViewPortHeight())
        viewPortTop = 1 - m_ChartViewer->getViewPortHeight();

    //
    // Update chart only if the view port has actually changed
    //
    if ((viewPortLeft != m_ChartViewer->getViewPortLeft()) ||
        (viewPortTop != m_ChartViewer->getViewPortTop()))
    {
        m_ChartViewer->setViewPortLeft(viewPortLeft);
        m_ChartViewer->setViewPortTop(viewPortTop);

        // Update the chart image only, but no need to update the image map.
        m_ChartViewer->updateViewPort(true, false);
    }
}

//
// QChartViewer ViewPortChanged event
//
void ZoomScrollDemo2::onViewPortChanged()
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
void ZoomScrollDemo2::updateControls(QChartViewer *viewer)
{
    //
    // Update the Zoom slider to reflect the current zoom level of the view port
    //
    double smallerSide = viewer->getViewPortWidth() > viewer->getViewPortHeight()
        ? viewer->getViewPortHeight() : viewer->getViewPortWidth();
    m_ZoomBar->setValue((int)(smallerSide * m_ZoomBar->maximum() + 0.5));

    //
    // Update the navigate window to reflect the current view port position and size. (Note:
    // we allowed for a 2-pixel margin for the frame border in the following computations.)
    //
    int borderWidth = m_NavigatePad->frameWidth();
    int left = (int)(viewer->getViewPortLeft() * (m_NavigatePad->width() - borderWidth * 2) + borderWidth + 0.5);
    int top = (int)(viewer->getViewPortTop() * (m_NavigatePad->height() - borderWidth * 2) + borderWidth + 0.5);
    int width = (int)(viewer->getViewPortWidth() * (m_NavigatePad->width() - borderWidth * 2) + 0.5);
    int height = (int)(viewer->getViewPortHeight() * (m_NavigatePad->height() - borderWidth * 2) + 0.5);
    m_NavigateWindow->setGeometry(left, top, width, height);
}

//
// User clicks on the QChartViewer
//
void ZoomScrollDemo2::onChartClicked(QMouseEvent *)
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
// Draw the chart and display it in the given viewer
//
void ZoomScrollDemo2::drawChart(QChartViewer *viewer)
{
    //
    // For simplicity, in this demo, we just use hard coded data. In a real application,
    // the data probably read from a dynamic source such as a database. (See the
    // ChartDirector documentation on "Using Data Sources with ChartDirector" if you need
    // some sample code on how to read data from database to array variables.)
    //
    double dataX0[] = {10, 15, 6, -12, 14, -8, 13, -3, 16, 12, 10.5, -7, 3, -10, -5, 2, 5};
    double dataY0[] = {130, 150, 80, 110, -110, -105, -130, -15, -170, 125,  125, 60, 25, 150,
        150,15, 120};
    double dataX1[] = {6, 7, -4, 3.5, 7, 8, -9, -10, -12, 11, 8, -3, -2, 8, 4, -15, 15};
    double dataY1[] = {65, -40, -40, 45, -70, -80, 80, 10, -100, 105, 60, 50, 20, 170, -25,
        50, 75};
    double dataX2[] = {-10, -12, 11, 8, 6, 12, -4, 3.5, 7, 8, -9, 3, -13, 16, -7.5, -10, -15};
    double dataY2[] = {65, -80, -40, 45, -70, -80, 80, 90, -100, 105, 60, -75, -150, -40, 120,
        -50, -30};

    // Create an XYChart object 500 x 480 pixels in size, with the same background color
    // as the container
    QColor bgColor = palette().color(backgroundRole()).rgb();
    XYChart *c = new XYChart(500, 480, (bgColor.red() << 16) + (bgColor.green() << 8) + bgColor.blue());

    // Set the plotarea at (50, 40) and of size 400 x 400 pixels. Use light grey (c0c0c0)
    // horizontal and vertical grid lines. Set 4 quadrant coloring, where the colors of
    // the quadrants alternate between lighter and deeper grey (dddddd/eeeeee).
    c->setPlotArea(50, 40, 400, 400, -1, -1, -1, 0xc0c0c0, 0xc0c0c0
        )->set4QBgColor(0xdddddd, 0xeeeeee, 0xdddddd, 0xeeeeee, 0x000000);

    // Enable clipping mode to clip the part of the data that is outside the plot area.
    c->setClipping();

    // Set 4 quadrant mode, with both x and y axes symetrical around the origin
    c->setAxisAtOrigin(Chart::XYAxisAtOrigin, Chart::XAxisSymmetric + Chart::YAxisSymmetric);

    // Add a legend box at (450, 40) (top right corner of the chart) with vertical layout
    // and 8 pts Arial Bold font. Set the background color to semi-transparent grey.
    LegendBox *legendBox = c->addLegend(450, 40, true, "arialbd.ttf", 8);
    legendBox->setAlignment(Chart::TopRight);
    legendBox->setBackground(0x40dddddd);

    // Add a titles to axes
    c->xAxis()->setTitle("Alpha Index");
    c->yAxis()->setTitle("Beta Index");

    // Set axes width to 2 pixels
    c->xAxis()->setWidth(2);
    c->yAxis()->setWidth(2);

    // The default ChartDirector settings has a denser y-axis grid spacing and less-dense
    // x-axis grid spacing. In this demo, we want the tick spacing to be symmetrical.
    // We use around 50 pixels between major ticks and 25 pixels between minor ticks.
    c->xAxis()->setTickDensity(50, 25);
    c->yAxis()->setTickDensity(50, 25);

    //
    // In this example, we represent the data by scatter points. If you want to represent
    // the data by somethings else (lines, bars, areas, floating boxes, etc), just modify
    // the code below to use the layer type of your choice.
    //

    // Add scatter layer, using 11 pixels red (ff33333) X shape symbols
    c->addScatterLayer(DoubleArray(dataX0, sizeof(dataX0) / sizeof(dataX0[0])),
        DoubleArray(dataY0, sizeof(dataY0) / sizeof(dataY0[0])), "Group A",
        Chart::Cross2Shape(), 11, 0xff3333);

    // Add scatter layer, using 11 pixels green (33ff33) circle symbols
    c->addScatterLayer(DoubleArray(dataX1, sizeof(dataX1) / sizeof(dataX1[0])),
        DoubleArray(dataY1, sizeof(dataY1) / sizeof(dataY1[0])),
        "Group B", Chart::CircleShape, 11,  0x33ff33);

    // Add scatter layer, using 11 pixels blue (3333ff) triangle symbols
    c->addScatterLayer(DoubleArray(dataX2, sizeof(dataX2) / sizeof(dataX2[0])),
        DoubleArray(dataY2, sizeof(dataY2) / sizeof(dataY2[0])),
        "Group C", Chart::TriangleSymbol, 11, 0x3333ff);

    if (m_maxX == m_minX)
    {
        // The axis scale has not yet been set up. So this is the first time the chart is
        // drawn and it is drawn with no zooming. We can use auto-scaling to determine the
        // axis-scales, then remember them for future use.

        // Explicitly auto-scale axes so we can get the axis scales
        c->layout();

        // Save the axis scales for future use
        m_minX = c->xAxis()->getMinValue();
        m_maxX = c->xAxis()->getMaxValue();
        m_minY = c->yAxis()->getMinValue();
        m_maxY = c->yAxis()->getMaxValue();
    }
    else
    {
        // Compute the zoomed-in axis scales using the overall axis scales and ViewPort size
        double xScaleMin = m_minX + (m_maxX - m_minX) * viewer->getViewPortLeft();
        double xScaleMax = m_minX + (m_maxX - m_minX) * (viewer->getViewPortLeft() +
            viewer->getViewPortWidth());
        double yScaleMin = m_maxY - (m_maxY - m_minY) * (viewer->getViewPortTop() +
            viewer->getViewPortHeight());
        double yScaleMax = m_maxY - (m_maxY - m_minY) * viewer->getViewPortTop();
        // *** use the following formula if you are using a log scale axis ***
        // double xScaleMin = minX * pow(maxX / minX, viewer->getViewPortLeft());
        // double xScaleMax = minX * pow(maxX / minX, viewer->getViewPortLeft() +
        //     viewer->getViewPortWidth());
        // double yScaleMin = maxY * pow(minY / maxY, viewer->getViewPortTop() +
        //    viewer->getViewPortHeight);
        // double yScaleMax = maxY * pow(minY / maxY, viewer->getViewPortTop());

        // Set the axis scales
        c->xAxis()->setLinearScale(xScaleMin, xScaleMax);
        c->xAxis()->setRounding(false, false);
        c->yAxis()->setLinearScale(yScaleMin, yScaleMax);
        c->yAxis()->setRounding(false, false);
    }

    // Set the chart image to the WinChartViewer
    delete viewer->getChart();
    viewer->setChart(c);
}

//
// Update the image map
//
void ZoomScrollDemo2::updateImageMap(QChartViewer *viewer)
{
    if (0 == viewer->getImageMapHandler())
    {
        // no existing image map - creates a new one
        viewer->setImageMap(viewer->getChart()->getHTMLImageMap("clickable", "",
                "title='[{dataSetName}] Alpha = {x}, Beta = {value}'"));
    }
}

//
// When the mouse enters the chart, we will generate an image map for hot spots and tooltips
// support if it has not already been generated.
//
void ZoomScrollDemo2::onMouseMove(QMouseEvent *)
{
    updateImageMap((QChartViewer *)QObject::sender());
}
