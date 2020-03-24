#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>

#include "interfaces/PaintSceneInterface.h"
#include "listeners/mainpresentorlistener.h"
#include "views/movingview.h"
#include "interfaces/mainwindowinterface.h"

class SelectorItem;
class MainInteractor;
class QAction;
class ProgressTrainingDialog;
class ArrowInteractorListener;

class PaintScene : public QGraphicsScene, public PaintSceneInterface, public MainPresentorListener
{
public:
    PaintScene(QObject *parent = nullptr);
    enum Mode {Selector, Views, Arrows, ScroolHandDrag};
    void setMode(Mode mode);
    void setViewType(MovingView::ViewType type);
    void setView(MainWindowInterface *interfaces);
    MovingView::ViewType getViewType();
    QPixmap getPerceptronIcon() const;
    QPixmap getDataIcon() const;
    void onDeleteBtnClicked();
    void onRunBtnClicked();
    void onAddOutputNeuronsActionClicked();
    void onStopActionClicked();
    void onPauseActionClicked();
    void onDebugActionClicked();
    void onLoadingActionClicked();
    void onSavingActionClicked();
    void setSelectedItemOutputsEnable(bool enable);

private:
    MainWindowInterface *view;
    MainInteractor* interactor;
    Mode mode;
    QGraphicsLineItem *line;
    SelectorItem *selector;
    MovingView::ViewType viewType;
    ProgressTrainingDialog *progressDialog;

private:
    void onTrainingStarted(unsigned int iterationCount, unsigned int epohCount) override;
    void onEpohChanged(unsigned int currentEpoh) override;
    void onIterationChanged(unsigned int currentIteration) override;
    void onErrorValueChanged(double value) override;
    void onTrainingFinished() override;
    void onNewPerceptronAdded(PerceptronInteractorListener *perceptron) override;
    void onNewDataAdded(DataInteractorListener *data) override;
    void onNewWeightAdded(ArrowInteractorListener *arrow, unsigned long startNeuronID, unsigned long endNeuronID) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void updateScene() override;
    void updateItem(QGraphicsItem *item) override;
    void moveSelectedItem(QPointF delta) override;
    void deleteItem(QGraphicsItem *item) override;
    QAction *getAction(int type) override;
    void clearSelectedItem() override;
    QStringList getOutputsNeuronsList() override;
    void addArrow();
    void addArrow(MovingView *startView, MovingView *endView);
    void addArrow(ArrowInteractorListener *listener, MovingView *startView, MovingView *endView);
    MovingView *findView(unsigned long neuronID);
    void addMovingView(QPointF position);
    void onViewsModePress(QGraphicsSceneMouseEvent *event);
    void onArrowsModePress(QGraphicsSceneMouseEvent *event);
    void onSelectorModePress(QGraphicsSceneMouseEvent *event);
    void onViewsModeMove(QGraphicsSceneMouseEvent *event);
    void onArrowsModeMove(QGraphicsSceneMouseEvent *event);
    void onSelectorModeMove(QGraphicsSceneMouseEvent *event);
    void onViewsModeRelease(QGraphicsSceneMouseEvent *event);
    void onArrowsModeRelease(QGraphicsSceneMouseEvent *event);
    void onSelectorModeRelease(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTSCENE_H
