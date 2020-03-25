#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "interfaces/mainwindowinterface.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class PaintScene;
class QButtonGroup;
class QComboBox;
class GraphicView;
class QSlider;
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public MainWindowInterface
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    PaintScene *scene;
    GraphicView *view;

    QAction *deleteAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *runAction;
    QAction *addOutputNeuronsAction;
    QAction *stopAction;
    QAction *pauseAction;
    QAction *debugAction;
    QAction *resetZoomAction;
    QAction *makeOutputNeuronAction;
    QAction *makeForwardNeuronAction;
    QAction *savingAction;
    QAction *loadingAction;

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

    QSlider *zoomSlider;

    //QToolBox *toolBox;

private:
    QAction *getAction(int type) override;
    void resizeEvent(QResizeEvent * event) override;
    QPointF getSceneTop() override;
    void zoomIn() override;
    void zoomOut() override;
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
    void onToolsGroupClicked(int id);
    void onRunActionClicked();
    void onAddOutputNeuronsActionClicked();
    void onStopActionClicked();
    void onPauseActionClicked();
    void onDebugActionClicked();
    void onZoomSliderValueChanged();
    void onResetZoomActionClicked();
    void onMakeOutputNeuronActionClicked();
    void onMakeForwardNeuronActionClicked();
    void onSaveActionClicked();
    void onOpenActionClicked();
};
#endif // MAINWINDOW_H
