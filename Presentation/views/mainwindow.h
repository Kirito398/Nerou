#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include <views/paintscene.h>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    PaintScene *scene;
    QGraphicsView *view;

    QAction *deleteAction;
    QAction *exitAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

private:
    void resizeEvent(QResizeEvent * event) override;
    void initActions();
    void initMenu();

private slots:
    void onEditModeBtnClicked();
    void onArrowModeBtnClicked();
    void onSelectorModeBtnClicked();
    void onDeleteActionClicked();
    void onExitActionClicked();
    void onAboutActionClicked();
};
#endif // MAINWINDOW_H
