#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QComboBox>
#include <QToolTip>
#include <QLabel>
#include <QToolBox>

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
    QAction *runAction;

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
};
#endif // MAINWINDOW_H
