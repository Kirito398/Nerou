#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <views/paintscene.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    PaintScene *scene;

private:
    void resizeEvent(QResizeEvent * event) override;

private slots:
    void onEditModeBtnClicked();
    void onArrowModeBtnClicked();
};
#endif // MAINWINDOW_H
