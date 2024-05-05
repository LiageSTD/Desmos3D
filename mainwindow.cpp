#include "mainwindow.h"

using namespace QtDataVisualization;

MainWindow::MainWindow(QWidget *widget)
    : QMainWindow(widget)
{
    surface = new QtDataVisualization::Q3DSurface();
    scatter = new QtDataVisualization::Q3DScatter();

    surface->setAxisX(new QtDataVisualization::QValue3DAxis);
    surface->setAxisY(new QtDataVisualization::QValue3DAxis);
    surface->setAxisZ(new QtDataVisualization::QValue3DAxis);

    scatter->setAxisX(new QtDataVisualization::QValue3DAxis);
    scatter->setAxisY(new QtDataVisualization::QValue3DAxis);
    scatter->setAxisZ(new QtDataVisualization::QValue3DAxis);

    QWidget *container = QWidget::createWindowContainer(surface);
    QSize screenSize = surface->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *scatterContainer = QWidget::createWindowContainer(scatter);
    scatterContainer->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    scatterContainer->setMaximumSize(screenSize);
    scatterContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scatterContainer->setFocusPolicy(Qt::StrongFocus);

    this->statusBar()->show();

    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(container);
    stackedWidget->addWidget(scatterContainer);

    savingSettings = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), "", this);
    savingSettings->setShortcuts(QKeySequence::Save);
    savingSettings->setStatusTip("Save state");
    connect(savingSettings, &QAction::triggered, this, &MainWindow::doSave);

    DownloadingSettings = new QAction(style()->standardIcon(QStyle::SP_DialogOpenButton), "", this);
    DownloadingSettings->setShortcuts(QKeySequence::Refresh);
    DownloadingSettings->setStatusTip("Revert state");
    connect(DownloadingSettings, &QAction::triggered, this, &MainWindow::doRevert);

    settings.setIniCodec("UTF-8");

    menu = menuBar()->addMenu("");
    langs = menuBar()->addMenu("");
    menu->addAction(savingSettings);
    menu->addAction(DownloadingSettings);

    QToolBar *toolBar = addToolBar("Toolbar");
    toolBar->addAction(savingSettings);
    toolBar->addAction(DownloadingSettings);

    langRus = new QAction("Русский", this);
    langEng = new QAction("English", this);
    langCn = new QAction("中文", this);
    langEm = new QAction("👅", this);

    langs->addAction(langRus);
    langs->addAction(langEng);
    langs->addAction(langCn);
    langs->addAction(langEm);

    QWidget *boxHLayout = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(boxHLayout);
    vidgetLayout = new QVBoxLayout();
    hLayout->addWidget(stackedWidget);
    hLayout->addLayout(vidgetLayout);
    setCentralWidget(boxHLayout);
    vidgetLayout->setAlignment(Qt::AlignTop);

    modeBox = new QGroupBox("");

    typeSur = new QRadioButton(widget);
    typeSc = new QRadioButton(widget);

    typeSur->setText("Scatter");
    typeSc->setText("Surface");

    typeSc->setChecked(true);
    typeSur->setChecked(false);

    QVBoxLayout *modePlotBox = new QVBoxLayout;
    modePlotBox->addWidget(typeSur);
    modePlotBox->addWidget(typeSc);
    modeBox->setLayout(modePlotBox);

    functionBox = new QGroupBox("");

    Sinc1 = new QRadioButton(widget);
    Sinc1->setText("Sinc1");

    Sinc2 = new QRadioButton(widget);
    Sinc2->setText("Sinc2");
    Sinc2->setChecked(false);

    QVBoxLayout *modelSubBox = new QVBoxLayout;
    modelSubBox->addWidget(Sinc1);
    modelSubBox->addWidget(Sinc2);
    functionBox->setLayout(modelSubBox);

    selectionGroupBox = new QGroupBox("");

    modeNoneRB = new QRadioButton(widget);
    modeNoneRB->setText("");
    modeNoneRB->setChecked(false);

    modeItemRB = new QRadioButton(widget);
    modeItemRB->setText("");
    modeItemRB->setChecked(true);

    QVBoxLayout *selectionVBox = new QVBoxLayout;
    selectionVBox->addWidget(modeNoneRB);
    selectionVBox->addWidget(modeItemRB);
    selectionGroupBox->setLayout(selectionVBox);

    gridSelection = new QGroupBox("");
    gridMode = new QCheckBox(widget);
    QVBoxLayout *gridSelectionVBox = new QVBoxLayout;
    gridSelectionVBox->addWidget(gridMode);
    gridSelection->setLayout(gridSelectionVBox);
    gridMode->setText("");

    labelSelection = new QGroupBox("");
    labelEnabled = new QCheckBox(widget);
    labelBorderEnabled = new QCheckBox(widget);

    labelEnabled->setText("");
    labelBorderEnabled->setText("");

    QVBoxLayout *labelSelectionSubBox = new QVBoxLayout;
    labelSelectionSubBox->addWidget(labelEnabled);
    labelSelectionSubBox->addWidget(labelBorderEnabled);

    labelSelection->setLayout(labelSelectionSubBox);

    stepsSelection = new QGroupBox("");
    QVBoxLayout *stepsSubBox = new QVBoxLayout;

    xSteps = new QSpinBox(widget);
    zSteps = new QSpinBox(widget);

    xSteps->setRange(1, 100);
    xSteps->setSingleStep(1);
    xSteps->setValue(50);

    zSteps->setRange(1, 100);
    zSteps->setSingleStep(1);
    zSteps->setValue(50);

    stepsSubBox->addWidget(xSteps);
    stepsSubBox->addWidget(zSteps);

    stepsSelection->setLayout(stepsSubBox);

    axisFromSliderX = new QSlider(Qt::Horizontal, widget);
    axisFromSliderX->setMinimum(0);
    axisFromSliderX->setTickInterval(1);
    axisFromSliderX->setEnabled(true);
    axisToSliderX = new QSlider(Qt::Horizontal, widget);
    axisToSliderX->setMinimum(1);
    axisToSliderX->setTickInterval(1);
    axisToSliderX->setEnabled(true);
    axisFromSliderZ = new QSlider(Qt::Horizontal, widget);
    axisFromSliderZ->setMinimum(0);
    axisFromSliderZ->setTickInterval(1);
    axisFromSliderZ->setEnabled(true);
    axisToSliderZ = new QSlider(Qt::Horizontal, widget);
    axisToSliderZ->setMinimum(1);
    axisToSliderZ->setTickInterval(1);
    axisToSliderZ->setEnabled(true);

    GradientBox = new QGroupBox(QStringLiteral("Gradients"));
    QPixmap pm(24, 100);
    QPainter pmp(&pm);

    QLinearGradient gradient1(0, 0, 1, 100);
    gradient1.setColorAt(1.0, Qt::black);
    gradient1.setColorAt(0.67, Qt::darkMagenta);
    gradient1.setColorAt(0.33, Qt::darkRed);
    gradient1.setColorAt(0.0, Qt::yellow);
    pmp.setBrush(QBrush(gradient1));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(0, 0, 24, 100);
    gradient1IcoButton = new QPushButton(widget);
    gradient1IcoButton->setIcon(QIcon(pm));
    gradient1IcoButton->setIconSize(QSize(24, 100));

    QLinearGradient gradient2(0, 0, 1, 100);
    gradient2.setColorAt(1.0, Qt::blue);
    gradient2.setColorAt(0.5, Qt::darkMagenta);
    gradient2.setColorAt(0.2, Qt::red);
    gradient2.setColorAt(0.0, Qt::magenta);
    pmp.setBrush(QBrush(gradient2));
    pmp.drawRect(0, 0, 24, 100);
    gradient2IcoButton = new QPushButton(widget);
    gradient2IcoButton->setIcon(QIcon(pm));
    gradient2IcoButton->setIconSize(QSize(24, 100));

    QHBoxLayout *colorSubBox = new QHBoxLayout;
    colorSubBox->addWidget(gradient1IcoButton);
    colorSubBox->addWidget(gradient2IcoButton);
    GradientBox->setLayout(colorSubBox);

    ZRange = new QLabel();
    XRange = new QLabel();
    vidgetLayout->addWidget(modeBox);
    vidgetLayout->addWidget(functionBox);
    vidgetLayout->addWidget(selectionGroupBox);
    vidgetLayout->addWidget(gridSelection);
    vidgetLayout->addWidget(labelSelection);
    vidgetLayout->addWidget(stepsSelection);
    vidgetLayout->addWidget(ZRange);
    vidgetLayout->addWidget(axisFromSliderX);
    vidgetLayout->addWidget(axisToSliderX);
    vidgetLayout->addWidget(XRange);
    vidgetLayout->addWidget(axisFromSliderZ);
    vidgetLayout->addWidget(axisToSliderZ);
    vidgetLayout->addWidget(GradientBox);
    setLayout(vidgetLayout);

    plot = new Plot(surface, scatter);

    plot->FromXSliderCh(axisFromSliderX);
    plot->FromZSliderCh(axisFromSliderZ);

    plot->ToXSliderCh(axisToSliderX);
    plot->ToZSliderCh(axisToSliderZ);

    QObject::connect(typeSur, &QRadioButton::toggled, this, &MainWindow::enableScatter);
    QObject::connect(typeSc, &QRadioButton::toggled, this, &MainWindow::enableSurface);
    QObject::connect(Sinc2, &QRadioButton::toggled, plot, &Plot::dislpaySinc2);
    QObject::connect(Sinc1, &QRadioButton::toggled, plot, &Plot::displaySinc1);

    QObject::connect(modeNoneRB, &QRadioButton::toggled, plot, &Plot::toggleModeNone);
    QObject::connect(modeItemRB, &QRadioButton::toggled, plot, &Plot::toggleModeItem);
    QObject::connect(gridMode, &QCheckBox::toggled, this, &MainWindow::toggleGrid);

    QObject::connect(labelEnabled, &QCheckBox::toggled, this, &MainWindow::toggleLabel);
    QObject::connect(labelBorderEnabled, &QCheckBox::toggled, this, &MainWindow::toggleBorderLabel);

    QObject::connect(xSteps,
                     QOverload<int>::of(&QSpinBox::valueChanged),
                     plot,
                     &Plot::changeAmountX);
    QObject::connect(zSteps,
                     QOverload<int>::of(&QSpinBox::valueChanged),
                     plot,
                     &Plot::changeAmountZ);

    QObject::connect(axisFromSliderX, &QSlider::valueChanged, plot, &Plot::adjustXMin);
    QObject::connect(axisToSliderX, &QSlider::valueChanged, plot, &Plot::adjustXMax);
    QObject::connect(axisFromSliderZ, &QSlider::valueChanged, plot, &Plot::adjustZMin);
    QObject::connect(axisToSliderZ, &QSlider::valueChanged, plot, &Plot::adjustZMax);

    QObject::connect(gradient1IcoButton,
                     &QPushButton::pressed,
                     this,
                     &MainWindow::setInfernoGradient);
    QObject::connect(gradient2IcoButton,
                     &QPushButton::pressed,
                     this,
                     &MainWindow::setStrangeGradient);

    QObject::connect(langRus, &QAction::triggered, this, &MainWindow::enableRus);

    QObject::connect(langEng, &QAction::triggered, this, &MainWindow::enableEng);

    QObject::connect(langCn, &QAction::triggered, this, &MainWindow::enableCn);
    QObject::connect(langEm, &QAction::triggered, this, &MainWindow::enableEm);
    QObject::connect(plot->Sinc1Series,
                     &QAbstract3DSeries::itemLabelChanged,
                     this,
                     &MainWindow::changeStatusBar);
    QObject::connect(plot->Sinc2Series,
                     &QAbstract3DSeries::itemLabelChanged,
                     this,
                     &MainWindow::changeStatusBar);

    doRevert();
    setNames();
    Sinc1->setChecked(true);
}
MainWindow::~MainWindow() {}

void MainWindow::toggleGrid(bool pressed)
{
    if (pressed) {
        surface->activeTheme()->setGridEnabled(false);
        scatter->activeTheme()->setGridEnabled(false);
    } else {
        surface->activeTheme()->setGridEnabled(true);
        scatter->activeTheme()->setGridEnabled(true);
    }
}

void MainWindow::toggleLabel(bool pressed)
{
    if (pressed) {
        surface->activeTheme()->setLabelTextColor(Qt::white);
        scatter->activeTheme()->setLabelTextColor(Qt::white);
        labelBorderEnabled->setChecked(true);
        labelBorderEnabled->setEnabled(false);
    } else {
        surface->activeTheme()->setLabelTextColor(Qt::black);
        scatter->activeTheme()->setLabelTextColor(Qt::black);
        labelBorderEnabled->setChecked(false);
        labelBorderEnabled->setEnabled(true);
    }
}

void MainWindow::toggleBorderLabel(bool pressed)
{
    if (pressed) {
        surface->activeTheme()->setLabelBorderEnabled(false);
        scatter->activeTheme()->setLabelBorderEnabled(false);
    } else {
        surface->activeTheme()->setLabelBorderEnabled(true);
        scatter->activeTheme()->setLabelBorderEnabled(true);
    }
}

void MainWindow::setInfernoGradient()
{
    if (Sinc1->isChecked()) {
        Sinc1Gradient1Enabled = true;
    } else {
        Sinc2Gradient1Enabled = true;
    }
    QLinearGradient gr;
    gr.setColorAt(0.0, QColor(0, 0, 4));
    gr.setColorAt(0.25, QColor(87, 16, 110));
    gr.setColorAt(0.5, QColor(188, 55, 84));
    gr.setColorAt(0.75, QColor(249, 142, 9));
    gr.setColorAt(1, QColor(252, 255, 164));

    surface->seriesList().at(0)->setBaseGradient(gr);
    surface->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
    scatter->seriesList().at(0)->setBaseGradient(gr);
    scatter->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void MainWindow::setStrangeGradient()
{
    QLinearGradient gr;
    gr.setColorAt(0.0, QColor(255, 165, 0));
    gr.setColorAt(0.25, QColor(0, 0, 255));
    gr.setColorAt(0.5, QColor(160, 32, 240));
    gr.setColorAt(0.75, QColor(255, 0, 0));
    gr.setColorAt(1, QColor(255, 192, 203));

    surface->seriesList().at(0)->setBaseGradient(gr);
    surface->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
    scatter->seriesList().at(0)->setBaseGradient(gr);
    scatter->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
}

void MainWindow::doSave()
{
    settings.setValue("gridMode", gridMode->isChecked());
    settings.setValue("labelEnabled", labelEnabled->isChecked());
    settings.setValue("labelBorderEnabled", labelBorderEnabled->isChecked());
    settings.setValue("Sinc1", Sinc1->isChecked());
    settings.setValue("modeItemRB", modeItemRB->isChecked());
    settings.setValue("xSteps", xSteps->value());
    settings.setValue("zSteps", zSteps->value());
    settings.setValue("axisFromSliderX", axisFromSliderX->value());
    settings.setValue("axisToSliderX", axisToSliderX->value());
    settings.setValue("axisFromSliderZ", axisFromSliderZ->value());
    settings.setValue("axisToSliderZ", axisToSliderZ->value());
    settings.setValue("Sinc1Gr1", Sinc1Gradient1Enabled);
    settings.setValue("Sinc2Gr1", Sinc2Gradient1Enabled);
}

void MainWindow::doRevert()
{
    gridMode->setChecked(settings.value("gridMode", false).toBool());

    labelEnabled->setChecked(settings.value("labelEnabled", false).toBool());

    labelBorderEnabled->setChecked(settings.value("labelBorderEnabled", false).toBool());

    if (settings.value("Sinc1", true).toBool()) {
        Sinc1->setChecked(true);
        if (settings.value("Sinc1Gr1", true).toBool()) {
            setInfernoGradient();
        } else {
            setStrangeGradient();
        }
    } else {
        Sinc2->setChecked(true);
        if (settings.value("Sinc2Gr1", true).toBool()) {
            setInfernoGradient();
        } else {
            setStrangeGradient();
        }
    }

    modeItemRB->setChecked(settings.value("modeItemRB", false).toBool());
    modeNoneRB->setChecked(!settings.value("modeItemRB", false).toBool());

    xSteps->setValue(settings.value("xSteps", 50).toInt());

    zSteps->setValue(settings.value("zSteps", 50).toInt());

    axisFromSliderX->setValue(settings.value("axisFromSliderX", 0).toInt());

    axisToSliderX->setValue(settings.value("axisToSliderX", 49).toInt());

    axisFromSliderZ->setValue(settings.value("axisFromSliderZ", 0).toInt());

    axisToSliderZ->setValue(settings.value("axisToSliderZ", 49).toInt());
}

void MainWindow::changeLang(QString lang)
{
    QApplication::removeTranslator(translator);
    translator = new QTranslator(this);
    translator->load(":/i18n/Language_" + lang);
    QApplication::installTranslator(translator);
    setNames();
}

void MainWindow::setNames()
{
    menu->setTitle(tr("Настройки"));
    langs->setTitle(tr("Языки"));

    savingSettings->setStatusTip(tr("Сохранить всё"));
    DownloadingSettings->setStatusTip(tr("Загрузить всё"));

    langRus->setStatusTip(tr("Русский"));
    langEng->setStatusTip(tr("Английский"));
    langCn->setStatusTip(tr("Китайский"));
    langEm->setStatusTip(tr("👅"));

    gridSelection->setTitle(tr("Сетка"));
    gridMode->setText(tr("Скрыть сетку"));

    labelSelection->setTitle(tr("Координаты"));
    labelEnabled->setText(tr("Скрыть координаты"));
    labelBorderEnabled->setText(tr("Скрыть окантовку координат"));

    functionBox->setTitle(tr("Графики функций"));

    modeBox->setTitle(tr("Режим"));

    selectionGroupBox->setTitle(tr("Отображение координат точки"));
    modeNoneRB->setText(tr("Выключить"));
    modeItemRB->setText(tr("Включить"));

    stepsSelection->setTitle(tr("Шаги"));

    ZRange->setText(tr("Z диапазон"));
    XRange->setText(tr("X диапазон"));

    GradientBox->setTitle(tr("Градиенты"));
}

void MainWindow::enableEng()
{
    MainWindow::changeLang("ENG");
}

void MainWindow::enableRus()
{
    MainWindow::changeLang("RU");
}

void MainWindow::enableCn()
{
    MainWindow::changeLang("CN");
}

void MainWindow::enableEm()
{
    MainWindow::changeLang("EM");
}

void MainWindow::changeStatusBar(const QString &label)
{
    if (!(label.isNull() || label.isEmpty())) {
        QStringList temp = label.split(" ");
        statusBar()->showMessage(QString("x = ") + temp[0] + QString(" y = ") + temp[1]
                                 + QString(" z = ") + temp[2]);
    } else {
        statusBar()->showMessage(QString(""));
    }
}
