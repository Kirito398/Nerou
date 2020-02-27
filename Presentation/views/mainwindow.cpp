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
    initToolBox();
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

QWidget *MainWindow::createToolBoxItem(const QString &name,  MoveItem::ItemType type) {
    MoveItem item(QPointF(0, 0), type);
    QIcon icon(item.getItemIcon());

    QToolButton *button = new QToolButton;
    button->setIcon(icon);
    button->setIconSize(QSize(50, 50));
    button->setCheckable(true);
    bgToolBox->addButton(button, type);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(button, 0, 0, Qt::AlignCenter);
    layout->addWidget(new QLabel(name), 1, 0, Qt::AlignCenter);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    return widget;
}

void MainWindow::initToolBox() {
    bgToolBox = new QButtonGroup;
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

    cbScale = new QComboBox;
    QStringList scales;
    scales << tr("25%") << tr("50%") << tr("100%") << tr("150%") << tr("200%") << tr("250%");
    cbScale->addItems(scales);
    cbScale->setCurrentIndex(2);
    cbScale->setToolTip(tr("Zoom"));
    cbScale->setStatusTip(tr("Zoom scene"));
    connect(cbScale, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onScaleChanged(const QString &)));

    toolsToolBar = addToolBar("Tools");
    toolsToolBar->addAction(deleteAction);
    toolsToolBar->addWidget(cbScale);
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

void MainWindow::onScaleChanged(const QString &scale) {
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

