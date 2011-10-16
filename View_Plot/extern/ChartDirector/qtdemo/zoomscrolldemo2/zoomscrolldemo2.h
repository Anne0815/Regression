#ifndef ZOOMSCROLLDEMO2_H
#define ZOOMSCROLLDEMO2_H

#include <QDialog>
#include <QSlider>
#include <QTimer>
#include <QPushButton>
#include "qdragrect.h"
#include "qchartviewer.h"


class ZoomScrollDemo2 : public QDialog {
    Q_OBJECT
public:
    ZoomScrollDemo2(QWidget *parent = 0);
    ~ZoomScrollDemo2();

private:

    double m_minX;		// The minimum overall x scale
    double m_maxX;		// The maximum overall x scale
    double m_minY;		// The minimum overall y scale
    double m_maxY;		// The maximum overall y scale

    QSlider *m_ZoomBar;
    QFrame *m_NavigatePad;
    QDragRect *m_NavigateWindow;

    QPushButton *m_UpLeftPB;
    QPushButton *m_UpPB;
    QPushButton *m_UpRightPB;
    QPushButton *m_LeftPB;
    QPushButton *m_CenterPB;
    QPushButton *m_RightPB;
    QPushButton *m_DownLeftPB;
    QPushButton *m_DownPB;
    QPushButton *m_DownRightPB;
    QTimer *m_RepeatButtonTimer;

    QChartViewer *m_ChartViewer;

    void scrollChartTo(double viewPortLeft, double viewPortTop);    // Scroll the chart
    void drawChart(QChartViewer *viewer);                           // Draw chart
    void updateImageMap(QChartViewer *viewer);                      // Update image map
    void updateControls(QChartViewer *viewer);                      // Update other controls

private slots:
    void onMouseUsageChanged(int mouseUsage);
    void onZoomBarChanged(int value);
    void onMovePB();
    void onNavigateWindowDrag(QPoint fromPoint, QPoint toPoint);
    void onMouseMove(QMouseEvent *event);
    void onViewPortChanged();
    void onChartClicked(QMouseEvent *event);
};

#endif // ZOOMSCROLLDEMO2_H
