#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "interfaces/mainwindowinterface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QAction;
class QMenu;
class PaintScene;
class QButtonGroup;
class QComboBox;
class QGraphicsView;
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public MainWindowInterface
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
    QAction *runAction;
    QAction *addOutputNeuronsAction;
    QAction *stopAction;
    QAction *pauseAction;
    QAction *debugAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *controlMenu;
    QMenu *aboutMenu;

    QToolBar *itemsToolBar;
    QToolBar *toolsToolBar;
    QToolBar *toolBoxToolBar;
    QToolBar *controlToolBar;

    QButtonGroup *bgItems;
    QButtonGroup *bgToolBox;

    QComboBox *cbScale;

    //QToolBox *toolBox;

private:
    QAction *getAction(int type) override;
    void resizeEvent(QResizeEvent * event) override;
    void initActions();
    void initMenu();
    void initToolBars();
    void initToolBox();
    void initControlToolBar();
    //QWidget *createToolBoxItem(const QString &name,  MoveItem::ItemType type);

private slots:
    void onItemsGroupClicked();
    void onDeleteActionClicked();
    void onExitActionClicked();
    void onAboutActionClicked();
    void onScaleChanged(const QString &scale);
    void onToolsGroupClicked(int id);
    void onRunActionClicked();
    void onAddOutputNeuronsActionClicked();
    void onStopActionClicked();
    void onPauseActionClicked();
    void onDebugActionClicked();
};
#endif // MAINWINDOW_H
