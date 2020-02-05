#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::resizeEvent(QResizeEvent * event) {
    QMainWindow::resizeEvent(event);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

