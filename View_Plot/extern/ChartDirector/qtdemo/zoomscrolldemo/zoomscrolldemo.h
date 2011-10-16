#ifndef ZOOMSCROLLDEMO_H
#define ZOOMSCROLLDEMO_H

#include <QDialog>
#include <QDateEdit>
#include <QComboBox>
#include <QScrollBar>
#include <QDateTime>
#include "qchartviewer.h"

class ZoomScrollDemo : public QDialog {
    Q_OBJECT
public:
    ZoomScrollDemo(QWidget *parent = 0);
    ~ZoomScrollDemo();

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

    double m_minDate;			// The earliest date (in chartTime unit)
    double m_dateRange;			// The overall duration (in seconds)
    double m_maxValue;			// The maximum overall y scale
    double m_minValue;			// The minimum overall y scale

    double m_currentDuration;           // The visible duration of the view port (in seconds)
    double m_minDuration;		// The maximum zoom-in limit (in seconds)

    QDateEdit *m_StartDate;
    QComboBox *m_Duration;
    QScrollBar *m_HScrollBar;
    QScrollBar *m_VScrollBar;
    QChartViewer *m_ChartViewer;

    void loadData();                            // Load data into data arrays
    void drawChart(QChartViewer *viewer);       // Draw chart
    void updateImageMap(QChartViewer *viewer);  // Update image map
    void updateControls(QChartViewer *viewer);  // Update other controls

private slots:
    void onDurationChanged(QString );
    void onStartDateChanged(QDateTime date);
    void onVScrollBarChanged(int value);
    void onHScrollBarChanged(int value);
    void onMouseUsageChanged(int mouseUsage);
    void onZoomModeChanged(int zoomMode);
    void onViewPortChanged();
    void onMouseMove(QMouseEvent *event);
    void onChartClicked(QMouseEvent *event);
};

#endif // ZOOMSCROLLDEMO_H
