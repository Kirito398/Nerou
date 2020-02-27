#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    initActions();
    initMenu();
    initToolBars();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    setCentralWidget(widget);
    setWindowTitle("Nerou");
    setUnifiedTitleAndToolBarOnMac(true);
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
    bgItems->addButton(tbAddItemMode, PaintScene::Items);
    bgItems->addButton(tbAddArrowMode, PaintScene::Arrows);
    connect(bgItems, SIGNAL(buttonClicked(int)), this, SLOT(onItemsGroupClicked()));

    itemsToolBar = addToolBar(tr("Items"));
    itemsToolBar->addWidget(tbSelectorMode);
    itemsToolBar->addWidget(tbAddItemMode);
    itemsToolBar->addWidget(tbAddArrowMode);

    toolsToolBar = addToolBar("Tools");
    toolsToolBar->addAction(deleteAction);
}

void MainWindow::initMenu() {
    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();

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
}

void MainWindow::onDeleteActionClicked() {
    QList<QGraphicsItem *> selectedItems = scene->selectedItems();

    for (auto item : selectedItems) {
        ArrowItem * arrowItem = dynamic_cast<ArrowItem *>(item);
        if (arrowItem == nullptr)
            continue;

        scene->removeItem(arrowItem);
        arrowItem->getStartItem()->removeArrow(arrowItem);
        arrowItem->getEndItem()->removeArrow(arrowItem);

        delete item;
    }

    selectedItems = scene->selectedItems();
    for (auto item : selectedItems) {
        MoveItem *moveItem = dynamic_cast<MoveItem *>(item);
        if (moveItem == nullptr)
            continue;

        moveItem->removeArrows();
        scene->removeItem(moveItem);
    }
}

void MainWindow::onItemsGroupClicked() {
    scene->setMode(PaintScene::Mode(bgItems->checkedId()));
}

void MainWindow::onExitActionClicked() {
    close();
}

void MainWindow::onAboutActionClicked() {
    QMessageBox::about(this, tr("About"), tr("Nerou project 2020"));
}

void MainWindow::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

