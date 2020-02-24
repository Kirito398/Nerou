#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showMaximized();

    scene = new PaintScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    connect(ui->pbEditMode, SIGNAL(clicked(bool)), this, SLOT(onEditModeBtnClicked()));
    connect(ui->pbArrowMode, SIGNAL(clicked(bool)), this, SLOT(onArrowModeBtnClicked()));
}

void MainWindow::onEditModeBtnClicked() {
    scene->setMode(PaintScene::Items);
}

void MainWindow::onArrowModeBtnClicked() {
    scene->setMode(PaintScene::Arrows);
}

void MainWindow::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

