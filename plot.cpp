#include "plot.h"

using namespace QtDataVisualization;

const float Plot::calculateTo = 10.0f;
const float Plot::calculateFrom = -10.0f;

int Plot::amountX = 50;
int Plot::amountZ = 50;

Plot::Plot(Q3DSurface *surface, Q3DScatter *scatter)
    : m_graph(surface)
    , m_scatter(scatter)
{
    Sinc1 = new QtDataVisualization::QSurfaceDataProxy();
    Sinc2 = new QtDataVisualization::QSurfaceDataProxy();
    Sinc1Scatter = new QtDataVisualization::QScatterDataProxy();
    Sinc2Scatter = new QtDataVisualization::QScatterDataProxy();

    Sinc1Series = new QtDataVisualization::QSurface3DSeries(Sinc1);
    Sinc2Series = new QtDataVisualization::QSurface3DSeries(Sinc2);
    Sinc1ScatterSeries = new QtDataVisualization::QScatter3DSeries(Sinc1Scatter);
    Sinc2ScatterSeries = new QtDataVisualization::QScatter3DSeries(Sinc2Scatter);

    m_graph->axisX()->setTitle("X");
    m_graph->axisX()->setTitleVisible(true);

    m_graph->axisY()->setTitle("Y");
    m_graph->axisY()->setTitleVisible(true);

    m_graph->axisZ()->setTitle("Z");
    m_graph->axisZ()->setTitleVisible(true);

    m_scatter->axisX()->setTitle("X");
    m_scatter->axisX()->setTitleVisible(true);

    m_scatter->axisY()->setTitle("Y");
    m_scatter->axisY()->setTitleVisible(true);

    m_scatter->axisZ()->setTitle("Z");
    m_scatter->axisZ()->setTitleVisible(true);

    fillSinc1Series();
    fillSinc2Series();
}

Plot::~Plot()
{
    delete Sinc1;
    delete Sinc2;
    delete Sinc1Scatter;
    delete Sinc2Scatter;

    delete Sinc1Series;
    delete Sinc2Series;
    delete Sinc1ScatterSeries;
    delete Sinc2ScatterSeries;
}

void Plot::fillSinc1Series()
{
    QSurfaceDataArray *calculated = new QSurfaceDataArray;
    QScatterDataArray *calculatedScatter = new QScatterDataArray;

    float stepX = (calculateTo - calculateFrom) / float(amountX - 1);
    float stepZ = (calculateTo - calculateFrom) / float(amountZ - 1);

    calculated->reserve(amountZ);
    for (int i = 0; i < amountZ; i++) {
        QSurfaceDataRow *littleArrayHelper = new QSurfaceDataRow(amountX);
        float z = qMin(calculateTo, (i * stepZ + calculateFrom));
        int index = 0;
        for (int j = 0; j < amountX; j++) {
            float x = qMin(calculateTo, (j * stepX + calculateFrom));
            float R = qSqrt(z * z + x * x) + 0.01f;
            float y = (qSin(R) / R + 0.24f) * 1.61f;
            (*littleArrayHelper)[index++].setPosition(QVector3D(x, y, z));
        }
        *calculated << littleArrayHelper;
    }

    calculatedScatter->resize(amountX * amountZ);

    QScatterDataItem *newScatterRow = &calculatedScatter->first();
    for (int i = 0; i < amountZ; i++) {
        float z = qMin(calculateTo, (i * stepZ + calculateFrom));
        for (int j = 0; j < amountX; j++) {
            float x = qMin(calculateTo, (j * stepX + calculateFrom));
            float R = qSqrt(z * z + x * x) + 0.01f;
            float y = (qSin(R) / R + 0.24f) * 1.61f;
            newScatterRow->setPosition(QVector3D(x, y, z));
            newScatterRow++;
        }
    }

    Sinc1Scatter->resetArray(calculatedScatter);
    Sinc1->resetArray(calculated);
}

void Plot::fillSinc2Series()
{
    QSurfaceDataArray *calculated = new QSurfaceDataArray;
    QScatterDataArray *calculatedScatter = new QScatterDataArray;

    float stepX = (calculateTo - calculateFrom) / float(amountX - 1);
    float stepZ = (calculateTo - calculateFrom) / float(amountZ - 1);

    calculated->reserve(amountZ);

    for (int i = 0; i < amountZ; i++) {
        QSurfaceDataRow *newRow = new QSurfaceDataRow(amountX);
        float z = qMin(calculateTo, (i * stepZ + calculateFrom));
        int index = 0;
        for (int j = 0; j < amountX; j++) {
            float x = qMin(calculateTo, (j * stepX + calculateFrom));
            float sincX = (x != 0.0f) ? (qSin(x) / x) : 1.0f;
            float sincZ = (z != 0.0f) ? (qSin(z) / z) : 1.0f;
            float y = sincX * sincZ;
            (*newRow)[index++].setPosition(QVector3D(x, y, z));
        }
        *calculated << newRow;
    }

    calculatedScatter->resize(amountX * amountZ);

    QScatterDataItem *newScatterRow = &calculatedScatter->first();
    for (int i = 0; i < amountZ; i++) {
        float z = qMin(calculateTo, (i * stepZ + calculateFrom));
        ;
        for (int j = 0; j < amountX; j++) {
            float x = qMin(calculateTo, (j * stepX + calculateFrom));
            float sincX = (x != 0.0f) ? (qSin(x) / x) : 1.0f;
            float sincZ = (z != 0.0f) ? (qSin(z) / z) : 1.0f;
            float y = sincX * sincZ;
            newScatterRow->setPosition(QVector3D(x, y, z));
            newScatterRow++;
        }
    }

    Sinc2->resetArray(calculated);
    Sinc2Scatter->resetArray(calculatedScatter);
}

void Plot::dislpaySinc2(bool enable)
{
    if (enable) {
        Sinc2Series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        Sinc2Series->setFlatShadingEnabled(true);

        m_graph->axisX()->setLabelFormat("%.2f");
        m_graph->axisZ()->setLabelFormat("%.2f");
        m_graph->axisX()->setRange(calculateFrom, calculateTo);
        m_graph->axisY()->setRange(-0.5f, 2.0f);
        m_graph->axisZ()->setRange(calculateFrom, calculateTo);
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);

        m_graph->removeSeries(Sinc1Series);
        m_graph->addSeries(Sinc2Series);

        m_scatter->axisX()->setLabelFormat("%.2f");
        m_scatter->axisZ()->setLabelFormat("%.2f");
        m_scatter->axisX()->setRange(calculateFrom, calculateTo);
        m_scatter->axisY()->setRange(-0.5f, 2.0f);
        m_scatter->axisZ()->setRange(calculateFrom, calculateTo);
        m_scatter->axisX()->setLabelAutoRotation(30);
        m_scatter->axisY()->setLabelAutoRotation(90);
        m_scatter->axisZ()->setLabelAutoRotation(30);

        m_scatter->removeSeries(Sinc1ScatterSeries);
        m_scatter->addSeries(Sinc2ScatterSeries);

        m_rangeMinX = calculateFrom;
        m_rangeMinZ = calculateFrom;
        m_stepX = (calculateTo - calculateFrom) / float(amountX - 1);
        m_stepZ = (calculateTo - calculateFrom) / float(amountZ - 1);
        fromXSlider->setMaximum(amountX - 2);
        fromXSlider->setValue(0);
        ToXSlider->setMaximum(amountX - 1);
        ToXSlider->setValue(amountX - 1);
        fromZSlider->setMaximum(amountZ - 2);
        fromZSlider->setValue(0);
        ToZSlider->setMaximum(amountZ - 1);
        ToZSlider->setValue(amountZ - 1);
    }
}

void Plot::displaySinc1(bool enable)
{
    if (enable) {
        Sinc1Series->setDrawMode(QSurface3DSeries::DrawSurfaceAndWireframe);
        Sinc1Series->setFlatShadingEnabled(true);

        m_graph->axisX()->setLabelFormat("%.2f");
        m_graph->axisZ()->setLabelFormat("%.2f");
        m_graph->axisX()->setRange(calculateFrom, calculateTo);
        m_graph->axisY()->setRange(-0.5f, 2.0f);
        m_graph->axisZ()->setRange(calculateFrom, calculateTo);
        m_graph->axisX()->setLabelAutoRotation(30);
        m_graph->axisY()->setLabelAutoRotation(90);
        m_graph->axisZ()->setLabelAutoRotation(30);

        m_graph->removeSeries(Sinc2Series);
        m_graph->addSeries(Sinc1Series);

        m_scatter->axisX()->setLabelFormat("%.2f");
        m_scatter->axisZ()->setLabelFormat("%.2f");
        m_scatter->axisX()->setRange(calculateFrom, calculateTo);
        m_scatter->axisY()->setRange(-0.5f, 2.0f);
        m_scatter->axisZ()->setRange(calculateFrom, calculateTo);
        m_scatter->axisX()->setLabelAutoRotation(30);
        m_scatter->axisY()->setLabelAutoRotation(90);
        m_scatter->axisZ()->setLabelAutoRotation(30);

        m_scatter->removeSeries(Sinc2ScatterSeries);
        m_scatter->addSeries(Sinc1ScatterSeries);

        m_rangeMinX = calculateFrom;
        m_rangeMinZ = calculateFrom;
        m_stepX = (calculateTo - calculateFrom) / float(amountX - 1);
        m_stepZ = (calculateTo - calculateFrom) / float(amountZ - 1);
        fromXSlider->setMaximum(amountX - 2);
        fromXSlider->setValue(0);
        ToXSlider->setMaximum(amountX - 1);
        ToXSlider->setValue(amountX - 1);
        fromZSlider->setMaximum(amountZ - 2);
        fromZSlider->setValue(0);
        ToZSlider->setMaximum(amountZ - 1);
        ToZSlider->setValue(amountZ - 1);
    }
}

void Plot::changeAmountX(int newStep)
{
    amountX = newStep + 1;

    fillSinc1Series();
    fillSinc2Series();
}
void Plot::changeAmountZ(int newStep)
{
    amountZ = newStep + 1;

    fillSinc1Series();
    fillSinc2Series();
}

void Plot::adjustXMin(int min)
{
    float minX = m_stepX * float(min) + m_rangeMinX;

    int max = ToXSlider->value();
    if (min >= max) {
        max = min + 1;
        ToXSlider->setValue(max);
    }
    float maxX = m_stepX * max + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void Plot::adjustXMax(int max)
{
    float maxX = m_stepX * float(max) + m_rangeMinX;

    int min = fromXSlider->value();
    if (max <= min) {
        min = max - 1;
        fromXSlider->setValue(min);
    }
    float minX = m_stepX * min + m_rangeMinX;

    setAxisXRange(minX, maxX);
}

void Plot::adjustZMin(int min)
{
    float minZ = m_stepZ * float(min) + m_rangeMinZ;

    int max = ToZSlider->value();
    if (min >= max) {
        max = min + 1;
        ToZSlider->setValue(max);
    }
    float maxZ = m_stepZ * max + m_rangeMinZ;

    setAxisZRange(minZ, maxZ);
}

void Plot::adjustZMax(int max)
{
    float maxX = m_stepZ * float(max) + m_rangeMinZ;

    int min = fromZSlider->value();
    if (max <= min) {
        min = max - 1;
        fromZSlider->setValue(min);
    }
    float minX = m_stepZ * min + m_rangeMinZ;

    setAxisZRange(minX, maxX);
}

void Plot::setAxisXRange(float from, float to)
{
    m_graph->axisX()->setRange(from, to);
    m_scatter->axisX()->setRange(from, to);
}

void Plot::setAxisZRange(float from, float to)
{
    m_graph->axisZ()->setRange(from, to);
    m_scatter->axisZ()->setRange(from, to);
}
