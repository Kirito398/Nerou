#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QComboBox>

#include <views/paintscene.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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
    Ui::MainWindow *ui;
    PaintScene *scene;
    QGraphicsView *view;

    QAction *deleteAction;
    QAction *exitAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

    QToolBar *itemsToolBar;
    QToolBar *toolsToolBar;

    QButtonGroup *bgItems;

    QComboBox *cbScale;

private:
    void resizeEvent(QResizeEvent * event) override;
    void initActions();
    void initMenu();
    void initToolBars();

private slots:
    void onItemsGroupClicked();
    void onDeleteActionClicked();
    void onExitActionClicked();
    void onAboutActionClicked();
    void onScaleChanged(const QString &scale);
};
#endif // MAINWINDOW_H
