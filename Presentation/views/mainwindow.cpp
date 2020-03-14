#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScreen>
#include <QToolButton>
#include <QToolBar>
#include <QComboBox>
#include <QMessageBox>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>

#include "views/paintscene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setView(this);

    initActions();
    initToolBox();
    initMenu();
    initToolBars();
    initControlToolBar();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //mainLayout->addWidget(toolBox);
    mainLayout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);
    setWindowTitle("Nerou");
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::initControlToolBar() {
    controlToolBar = addToolBar(tr("Control"));
    controlToolBar->addAction(runAction);
    controlToolBar->addAction(debugAction);
    controlToolBar->addAction(pauseAction);
    controlToolBar->addAction(stopAction);
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
    //tbConvolution->setIcon(QIcon(item->getItemIcon()));
    tbConvolution->setToolTip(tr("Convolution"));
    tbConvolution->setStatusTip(tr("Add convolution"));
    //delete item;
    //item = 0;

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

    toolBoxToolBar = new QToolBar;
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

    bgItems = new QButtonGroup(this);
    bgItems->addButton(tbSelectorMode, PaintScene::Selector);
    bgItems->addButton(tbAddItemMode, PaintScene::Views);
    bgItems->addButton(tbAddArrowMode, PaintScene::Arrows);
    connect(bgItems, SIGNAL(buttonClicked(int)), this, SLOT(onItemsGroupClicked()));

    itemsToolBar = addToolBar(tr("Items"));
    itemsToolBar->addWidget(tbSelectorMode);
    itemsToolBar->addWidget(tbAddItemMode);
    itemsToolBar->addWidget(tbAddArrowMode);

    cbScale = new QComboBox;
    QStringList scales;
    scales << tr("25%") << tr("50%") << tr("100%") << tr("150%") << tr("200%") << tr("250%");
    cbScale->addItems(scales);
    cbScale->setCurrentIndex(2);
    cbScale->setToolTip(tr("Zoom"));
    cbScale->setStatusTip(tr("Zoom scene"));
    connect(cbScale, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onScaleChanged(const QString &)));

    toolsToolBar = addToolBar("Tools");
    toolsToolBar->addAction(addOutputNeuronsAction);
    toolsToolBar->addAction(deleteAction);
    toolsToolBar->addWidget(cbScale);

    //addToolBar(Qt::TopToolBarArea, toolsToolBar);
}

void MainWindow::initMenu() {
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("Item"));
    itemMenu->addAction(addOutputNeuronsAction);
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
}

void MainWindow::onExitActionClicked() {
    close();
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

void MainWindow::onScaleChanged(const QString &scale) {
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

QAction *MainWindow::getAction(int type) {
    switch (type) {
        case AddOutputNeurons : return addOutputNeuronsAction;
        case Delete : return deleteAction;
        default: return nullptr;
    }
}

void MainWindow::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
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

