#ifndef PLOT_H
#define PLOT_H

#include <Q3DSurface>
#include <QSlider>
#include <QWidget>
#include <QtDataVisualization>

class Plot : public QWidget
{
public:
    static int amountX;
    static int amountZ;

    static const float calculateFrom;
    static const float calculateTo;

    Plot(QtDataVisualization::Q3DSurface *surface, QtDataVisualization::Q3DScatter *scatter);

    QtDataVisualization::QSurfaceDataProxy *Sinc1;
    QtDataVisualization::QSurfaceDataProxy *Sinc2;
    QtDataVisualization::QScatterDataProxy *Sinc1Scatter;
    QtDataVisualization::QScatterDataProxy *Sinc2Scatter;

    QtDataVisualization::QSurface3DSeries *Sinc1Series;
    QtDataVisualization::QSurface3DSeries *Sinc2Series;
    QtDataVisualization::QScatter3DSeries *Sinc1ScatterSeries;
    QtDataVisualization::QScatter3DSeries *Sinc2ScatterSeries;

    void fillSinc1Series();
    void fillSinc2Series();

    void displaySinc1(bool enable);
    void dislpaySinc2(bool enable);

    void FromXSliderCh(QSlider *slider) { fromXSlider = slider; }
    void FromZSliderCh(QSlider *slider) { fromZSlider = slider; }

    void ToXSliderCh(QSlider *slider) { ToXSlider = slider; }
    void ToZSliderCh(QSlider *slider) { ToZSlider = slider; }

    void adjustXMin(int min);
    void adjustXMax(int max);
    void adjustZMin(int min);
    void adjustZMax(int max);

    void toggleModeNone()
    {
        m_graph->setSelectionMode(QtDataVisualization::QAbstract3DGraph::SelectionNone);
        m_scatter->setSelectionMode(QtDataVisualization::QAbstract3DGraph::SelectionNone);
    }
    void toggleModeItem()
    {
        m_graph->setSelectionMode(QtDataVisualization::QAbstract3DGraph::SelectionItem);
        m_scatter->setSelectionMode(QtDataVisualization::QAbstract3DGraph::SelectionItem);
    }

    ~Plot();

public slots:
    void changeAmountX(int newStep);
    void changeAmountZ(int newStep);

private:
    float m_rangeMinX;
    float m_rangeMinZ;

    float m_stepX;
    float m_stepZ;

    QtDataVisualization::Q3DSurface *m_graph;
    QtDataVisualization::Q3DScatter *m_scatter;

    QSlider *fromXSlider, *fromZSlider;
    QSlider *ToXSlider, *ToZSlider;

    void setAxisXRange(float from, float to);
    void setAxisZRange(float from, float to);
};

#endif
