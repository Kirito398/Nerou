#include "mainwindow.h"

#include <QScreen>
#include <QToolButton>
#include <QToolBar>
#include <QComboBox>
#include <QMessageBox>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QtMath>
#include <QSlider>
#include <QStatusBar>
#include <QSplitter>

#ifndef QT_NO_OPEN_GL
#include <QGLWidget>
#include <QGLFormat>
#endif

#include "views/paintscene.h"
#include "views/graphicview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene = new PaintScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setView(this);

    initActions();
    initToolBox();
    initMenu();
    initToolBars();
    initControlToolBar();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    view = new GraphicView(this, scene);

    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::NoDrag);
    view->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    #ifndef QT_NO_OPEN_GL
    QGLFormat format(QGL::SampleBuffers);
    QGLWidget *openGL = new QGLWidget(format);
    view->setViewport(openGL);
    #endif

    //mainLayout->addWidget(toolBox);
    mainLayout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    QSplitter *vSplitter = new QSplitter;
    vSplitter->setOrientation(Qt::Horizontal);

    vSplitter->addWidget(widget);
    vSplitter->addWidget(initPropertiesToolBar());

    vSplitter->setStretchFactor(0, 20);
    vSplitter->setStretchFactor(1, 1);

    setCentralWidget(vSplitter);
    setWindowTitle("Nerou");
    setUnifiedTitleAndToolBarOnMac(true);

    QStatusBar *statusBar = new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusbar"));
    setStatusBar(statusBar);

    this->resize(800, 600);
    this->showMaximized();
}

QPointF MainWindow::getSceneTop() {
    return geometry().topLeft() + view->geometry().topLeft();
}

void MainWindow::initControlToolBar() {
    controlToolBar = addToolBar(tr("Control"));
    controlToolBar->addAction(runAction);
    controlToolBar->addAction(debugAction);
    controlToolBar->addAction(pauseAction);
    controlToolBar->addAction(stopAction);
    controlToolBar->addAction(resetZoomAction);
}

void MainWindow::initToolBox() {
    QToolButton *tbPerceptron = new QToolButton;
    tbPerceptron->setCheckable(true);
    tbPerceptron->setIcon(QIcon(scene->getPerceptronIcon()));
    tbPerceptron->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    tbPerceptron->setToolTip(tr("Perceptron"));
    tbPerceptron->setStatusTip(tr("Add perceptron"));

    QToolButton *tbConvolution = new QToolButton;
    tbConvolution->setCheckable(true);
    tbConvolution->setIcon(scene->getConvolutionIcon());
    tbConvolution->setToolTip(tr("Convolution"));
    tbConvolution->setStatusTip(tr("Add convolution"));

    QToolButton *tbData = new QToolButton;
    tbData->setCheckable(true);
    tbData->setIcon(QIcon(scene->getDataIcon()));
    tbData->setToolTip(tr("Data"));
    tbData->setStatusTip(tr("Add data"));

    bgToolBox = new QButtonGroup(this);
    bgToolBox->setExclusive(false);
    bgToolBox->addButton(tbPerceptron, MovingView::Perceptron);
    bgToolBox->addButton(tbConvolution, MovingView::Convolution);
    bgToolBox->addButton(tbData, MovingView::Data);
    connect(bgToolBox, SIGNAL(buttonClicked(int)), this, SLOT(onToolsGroupClicked(int)));

    toolBoxToolBar = new QToolBar(tr("Blocks"));
    toolBoxToolBar->addWidget(tbData);
    toolBoxToolBar->addWidget(tbPerceptron);
    toolBoxToolBar->addWidget(tbConvolution);
    addToolBar(Qt::LeftToolBarArea, toolBoxToolBar);
}

void MainWindow::onToolsGroupClicked(int id) {
    QList<QAbstractButton *> buttons = bgToolBox->buttons();

    for(auto *button : buttons) {
        if (bgToolBox->button(id) != button)
            button->setChecked(false);
    }

    bgToolBox->button(id)->setChecked(true);
    bgItems->button(PaintScene::Views)->setChecked(true);

    scene->setMode(PaintScene::Views);
    scene->setViewType(MovingView::ViewType(id));

    view->setDragMode(QGraphicsView::NoDrag);
}

void MainWindow::initToolBars() {
    QToolButton *tbSelectorMode = new QToolButton;
    tbSelectorMode->setCheckable(true);
    tbSelectorMode->setChecked(true);
    tbSelectorMode->setIcon(QIcon(":/images/select_icon.png"));
    tbSelectorMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    tbSelectorMode->setToolTip(tr("Select and Move"));
    tbSelectorMode->setStatusTip(tr("Select or move items"));

    QToolButton *tbAddItemMode = new QToolButton;
    tbAddItemMode->setCheckable(true);
    tbAddItemMode->setIcon(QIcon(":images/add_item_icon.png"));
    tbAddItemMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
    tbAddItemMode->setToolTip(tr("Add item"));
    tbAddItemMode->setStatusTip(tr("Add new item"));

    QToolButton *tbAddArrowMode = new QToolButton;
    tbAddArrowMode->setCheckable(true);
    tbAddArrowMode->setIcon(QIcon(":/images/add_arrow_icon.png"));
    tbAddArrowMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    tbAddArrowMode->setToolTip(tr("Add arrow"));
    tbAddArrowMode->setStatusTip(tr("Create items relations"));

    QToolButton *tbScroolHandDragMode = new QToolButton;
    tbScroolHandDragMode->setCheckable(true);
    tbScroolHandDragMode->setIcon(QIcon(":/images/scrool_hand_drag_icon.png"));
    tbScroolHandDragMode->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
    tbScroolHandDragMode->setToolTip(tr("Hand drag"));
    tbScroolHandDragMode->setStatusTip(tr("Scrool hand drag mode"));

    bgItems = new QButtonGroup(this);
    bgItems->addButton(tbSelectorMode, PaintScene::Selector);
    bgItems->addButton(tbAddItemMode, PaintScene::Views);
    bgItems->addButton(tbAddArrowMode, PaintScene::Arrows);
    bgItems->addButton(tbScroolHandDragMode, PaintScene::ScroolHandDrag);
    connect(bgItems, SIGNAL(buttonClicked(int)), this, SLOT(onItemsGroupClicked()));

    itemsToolBar = addToolBar(tr("Items"));
    itemsToolBar->addWidget(tbSelectorMode);
    itemsToolBar->addWidget(tbAddItemMode);
    itemsToolBar->addWidget(tbAddArrowMode);
    itemsToolBar->addWidget(tbScroolHandDragMode);

    toolsToolBar = addToolBar("Tools");
    toolsToolBar->addAction(addOutputNeuronsAction);
    toolsToolBar->addAction(makeOutputNeuronAction);
    toolsToolBar->addAction(makeForwardNeuronAction);
    toolsToolBar->addAction(deleteAction);

    zoomSlider = new QSlider();
    zoomSlider->setMinimum(0);
    zoomSlider->setMaximum(500);
    zoomSlider->setValue(250);
    zoomSlider->setTickPosition(QSlider::TicksBelow);
    zoomSlider->setOrientation(Qt::Horizontal);
    connect(zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(onZoomSliderValueChanged()));

    QToolBar *zoomToolBar = new QToolBar(tr("Zoom"));
    zoomToolBar->addWidget(zoomSlider);
    addToolBar(Qt::BottomToolBarArea, zoomToolBar);
}

void MainWindow::initMenu() {
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(loadingAction);
    fileMenu->addAction(savingAction);
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("Item"));
    itemMenu->addAction(addOutputNeuronsAction);
    itemMenu->addAction(makeOutputNeuronAction);
    itemMenu->addAction(makeForwardNeuronAction);
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();

    controlMenu = menuBar()->addMenu(tr("Run"));
    controlMenu->addAction(runAction);

    aboutMenu = menuBar()->addMenu(tr("Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::initActions() {
    deleteAction = new QAction(QIcon(":/images/delete_icon.png"), tr("Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip("Delete item");
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(onDeleteActionClicked()));

    exitAction = new QAction(QIcon(":/images/exit_icon.png") ,tr("Exit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit"));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(onExitActionClicked()));

    aboutAction = new QAction(QIcon(":/images/about_icon.png"), tr("About"), this);
    aboutAction->setShortcut(tr("F1"));
    aboutAction->setStatusTip(tr("About"));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(onAboutActionClicked()));

    runAction = new QAction(QIcon(":/images/run_icon.png"), tr("Run"), this);
    runAction->setStatusTip(tr("Run"));
    connect(runAction, SIGNAL(triggered(bool)), this, SLOT(onRunActionClicked()));

    addOutputNeuronsAction = new QAction(QIcon(":/images/add_neurons_icon.png"), tr("Add Output Neurons"), this);
    addOutputNeuronsAction->setStatusTip(tr("Add output neurons"));
    connect(addOutputNeuronsAction, SIGNAL(triggered(bool)), this, SLOT(onAddOutputNeuronsActionClicked()));

    stopAction = new QAction(QIcon(":/images/stop_icon.png"), tr("Stop"), this);
    stopAction->setStatusTip(tr("Stop process"));
    connect(stopAction, SIGNAL(triggered(bool)), this, SLOT(onStopActionClicked()));

    pauseAction = new QAction(QIcon(":/images/pause_icon.png"), tr("Pause"), this);
    pauseAction->setStatusTip(tr("Pause process"));
    connect(pauseAction, SIGNAL(triggered(bool)), this, SLOT(onPauseActionClicked()));

    debugAction = new QAction(QIcon(":/images/debug_icon.png"), tr("Debug"), this);
    debugAction->setStatusTip(tr("Start debug"));
    connect(debugAction, SIGNAL(triggered(bool)), this, SLOT(onDebugActionClicked()));

    resetZoomAction = new QAction(QIcon(":/images/zoom_reset_icon.png"), tr("Reset zoom"), this);
    resetZoomAction->setStatusTip(tr("Reset scene zoom"));
    connect(resetZoomAction, SIGNAL(triggered(bool)), this, SLOT(onResetZoomActionClicked()));

    makeOutputNeuronAction = new QAction(QIcon(":/images/output_neuron_icon.png"), tr("Make output neuron"));
    makeOutputNeuronAction->setStatusTip(tr("Make selected neuron to the output neuron"));
    connect(makeOutputNeuronAction, SIGNAL(triggered(bool)), this, SLOT(onMakeOutputNeuronActionClicked()));

    makeForwardNeuronAction = new QAction(QIcon(":/images/forward_neuron_icon.png"), tr("Make forward neuron"));
    makeForwardNeuronAction->setStatusTip(tr("Make selected neuron to the forward neuron"));
    connect(makeForwardNeuronAction, SIGNAL(triggered(bool)), this, SLOT(onMakeForwardNeuronActionClicked()));

    savingAction = new QAction(QIcon(":/images/save_icon.png"), tr("Save project"));
    savingAction->setStatusTip(tr("Save project"));
    savingAction->setShortcuts(QKeySequence::Save);
    connect(savingAction, SIGNAL(triggered(bool)), this, SLOT(onSaveActionClicked()));

    loadingAction = new QAction(QIcon(":/images/open_icon.png"), tr("Open project"));
    loadingAction->setStatusTip(tr("Open project"));
    loadingAction->setShortcuts(QKeySequence::Open);
    connect(loadingAction, SIGNAL(triggered(bool)), this, SLOT(onOpenActionClicked()));
}

void MainWindow::onAddOutputNeuronsActionClicked() {
    bgItems->button(PaintScene::Selector)->setChecked(true);
    onItemsGroupClicked();

    scene->onAddOutputNeuronsActionClicked();
}

void MainWindow::onDeleteActionClicked() {
    scene->onDeleteBtnClicked();
}

void MainWindow::onItemsGroupClicked() {
    scene->setMode(PaintScene::Mode(bgItems->checkedId()));

    if (bgToolBox->checkedId() != -1)
        bgToolBox->button(bgToolBox->checkedId())->setChecked(false);

    if (PaintScene::Mode(bgItems->checkedId()) == PaintScene::Views)
        bgToolBox->button(scene->getViewType())->setChecked(true);

    if (PaintScene::Mode(bgItems->checkedId()) == PaintScene::ScroolHandDrag)
        view->setDragMode(QGraphicsView::ScrollHandDrag);
    else
        view->setDragMode(QGraphicsView::NoDrag);
}

void MainWindow::onResetZoomActionClicked() {
    zoomSlider->setValue(250);
}

void MainWindow::onExitActionClicked() {
    close();
}

void MainWindow::onSaveActionClicked() {
    scene->onSavingActionClicked();
}

void MainWindow::onOpenActionClicked(){
    scene->onLoadingActionClicked();
}

void MainWindow::onAboutActionClicked() {
    QMessageBox::about(this, tr("About"), tr("Nerou project 2020"));
}

void MainWindow::onRunActionClicked() {
    scene->onRunBtnClicked();
}

void MainWindow::onStopActionClicked() {
    scene->onStopActionClicked();
}

void MainWindow::onPauseActionClicked() {
    scene->onPauseActionClicked();
}

void MainWindow::onDebugActionClicked() {
    scene->onDebugActionClicked();
}

void MainWindow::onMakeOutputNeuronActionClicked() {
    scene->setSelectedItemOutputsEnable(true);
}

void MainWindow::onMakeForwardNeuronActionClicked() {
    scene->setSelectedItemOutputsEnable(false);
}

void MainWindow::zoomIn() {
    zoomSlider->setValue(zoomSlider->value() + 6);
    view->update();
}

void MainWindow::zoomOut() {
    zoomSlider->setValue(zoomSlider->value() - 6);
    view->update();
}

void MainWindow::updateWindow() {
    update();
}

void MainWindow::onZoomSliderValueChanged() {
    qreal scale = qPow(qreal(2), (zoomSlider->value() - 250) / qreal(50));

    QMatrix matrix;
    matrix.scale(scale, scale);

    view->setMatrix(matrix);
}

QAction *MainWindow::getAction(int type) {
    switch (type) {
        case AddOutputNeurons : return addOutputNeuronsAction;
        case Delete : return deleteAction;
        case MakeOutputNeuron : return makeOutputNeuronAction;
        case MakeForwardNeuron : return makeForwardNeuronAction;
        default: return nullptr;
    }
}

void MainWindow::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    delete scene;
}

QWidget *MainWindow::initPropertiesToolBar() {
    QBoxLayout *propertiesLayout = new QVBoxLayout();

    QWidget *widget = new QWidget;
    widget->setLayout(propertiesLayout);

    scene->setPropertiesLayout(propertiesLayout);

    return widget;
}

//QWidget *MainWindow::createToolBoxItem(const QString &name,  MoveItem::ItemType type) {
//    MoveItem item(QPointF(0, 0), type);
//    QIcon icon(item.getItemIcon());

//    QToolButton *button = new QToolButton;
//    button->setIcon(icon);
//    button->setIconSize(QSize(25, 25));
//    button->setCheckable(true);
//    bgToolBox->addButton(button, type);

//    QGridLayout *layout = new QGridLayout;
//    layout->addWidget(button, 0, 0, Qt::AlignCenter);
//    layout->addWidget(new QLabel(name), 0, 1, Qt::AlignCenter);

//    QWidget *widget = new QWidget;
//    widget->setLayout(layout);

//    return widget;
//}

//void MainWindow::initToolBox() {
//    bgToolBox = new QButtonGroup(this);
//    bgToolBox->setExclusive(false);
//    connect(bgToolBox, SIGNAL(buttonClicked(int)), this, SLOT(onToolsGroupClicked(int)));

//    QGridLayout *layout = new QGridLayout;
//    layout->addWidget(createToolBoxItem(tr("Perceptron"), MoveItem::Perceptron));
//    layout->addWidget(createToolBoxItem(tr("Perceptron"), MoveItem::Perceptron));
//    layout->addWidget(createToolBoxItem(tr("Perceptron"), MoveItem::Perceptron));
//    layout->addWidget(createToolBoxItem(tr("Perceptron"), MoveItem::Perceptron));
//    layout->addWidget(createToolBoxItem(tr("Perceptron"), MoveItem::Perceptron));

//    layout->setRowStretch(5, 5);
//    layout->setColumnStretch(5, 5);

//    QWidget *itemWidget = new QWidget;
//    itemWidget->setLayout(layout);

//    toolBox = new QToolBox;
//    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
//    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
//    toolBox->addItem(itemWidget, tr("Items"));
//}

//void MainWindow::onToolsGroupClicked(int id) {
//    QList<QAbstractButton *> buttons = bgToolBox->buttons();

//    for(auto *button : buttons) {
//        if (bgToolBox->button(id) != button)
//            button->setChecked(false);
//    }

//    bgItems->button(PaintScene::Items)->setChecked(true);
//    scene->setMode(PaintScene::Items);
//}

