#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initActions();
    initMenu();

    //showMaximized();

    scene = new PaintScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    connect(ui->pbEditMode, SIGNAL(clicked(bool)), this, SLOT(onEditModeBtnClicked()));
    connect(ui->pbArrowMode, SIGNAL(clicked(bool)), this, SLOT(onArrowModeBtnClicked()));
    connect(ui->pbMoveMode, SIGNAL(clicked(bool)), this, SLOT(onSelectorModeBtnClicked()));
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
    deleteAction = new QAction(tr("Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip("Delete item");
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(onDeleteActionClicked()));

    exitAction = new QAction(tr("Exit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Neuro"));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(onExitActionClicked()));

    aboutAction = new QAction(tr("About"), this);
    aboutAction->setShortcut(tr("F1"));
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

void MainWindow::onExitActionClicked() {
    close();
}

void MainWindow::onAboutActionClicked() {
    QMessageBox::about(this, tr("About"), tr("Nerou project 2020"));
}

void MainWindow::onEditModeBtnClicked() {
    scene->setMode(PaintScene::Items);
}

void MainWindow::onArrowModeBtnClicked() {
    scene->setMode(PaintScene::Arrows);
}

void MainWindow::onSelectorModeBtnClicked() {
    scene->setMode(PaintScene::Selector);
}

void MainWindow::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

