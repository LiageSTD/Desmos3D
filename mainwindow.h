#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "plot.h"
#include <QAction>
#include <QApplication>
#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QSpinBox>
#include <QStackedWidget>
#include <QStatusBar>
#include <QStyle>
#include <QToolBar>
#include <QVBoxLayout>
#include <QtDataVisualization>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    Plot *plot;
    QtDataVisualization::Q3DSurface *surface;
    QtDataVisualization::Q3DScatter *scatter;

    void toggleGrid(bool pressed);
    void handleGrid();

    void toggleLabel(bool pressed);
    void toggleBorderLabel(bool pressed);

    void setInfernoGradient();
    void setStrangeGradient();

    void changeStatusBar(const QString &label);
    void enableScatter(bool flag)
    {
        if (flag) {
            stackedWidget->setCurrentIndex(1);
        }
    };
    void enableSurface(bool flag)
    {
        if (flag) {
            stackedWidget->setCurrentIndex(0);
        }
    };
    ;

    ~MainWindow();

public slots:
    void doSave();
    void doRevert();

    void enableEng();
    void enableRus();
    void enableCn();
    void enableEm();

private:
    bool Sinc1Gradient1Enabled, Sinc2Gradient1Enabled;
    QSettings settings;
    QAction *savingSettings, *DownloadingSettings;

    QTranslator *translator;
    QAction *langRus, *langEng, *langCn, *langEm;

    QGroupBox *functionBox, *selectionGroupBox, *gridSelection, *labelSelection, *stepsSelection,
        *GradientBox, *typeSelectionBox, *modeBox;

    QLinearGradient gradient1, gradient2;

    QVBoxLayout *vidgetLayout;
    QLabel *ZRange, *XRange;

    QMenu *menu, *langs;
    QRadioButton *Sinc1, *Sinc2;
    QRadioButton *typeSur, *typeSc;
    QRadioButton *modeNoneRB, *modeItemRB;
    QCheckBox *gridMode, *labelEnabled, *labelBorderEnabled;
    QPushButton *gradient1IcoButton, *gradient2IcoButton;
    QSlider *axisFromSliderX, *axisToSliderX;
    QSlider *axisFromSliderZ, *axisToSliderZ;
    QSpinBox *xSteps, *zSteps;

    QStackedWidget *stackedWidget;

    void changeLang(QString lang);

    void setNames();
};
#endif
