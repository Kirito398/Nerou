#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>

#include "interfaces/PaintSceneInterface.h"
#include "listeners/mainpresentorlistener.h"
#include "views/movingview.h"

class SelectorItem;
class MainInteractor;
class QAction;

class PaintScene : public QGraphicsScene, public PaintSceneInterface, public MainPresentorListener
{
public:
    PaintScene(QObject *parent = nullptr);
    enum Mode {Selector, Views, Arrows};
    void setMode(Mode mode);
    void setViewType(MovingView::ViewType type);
    MovingView::ViewType getViewType();
    QPixmap getPerceptronIcon() const;
    QPixmap getDataIcon() const;
    void onDeleteBtnClicked();
    void onRunBtnClicked();;
    void setDeleteAction(QAction *action);

private:
    MainInteractor* interactor;
    Mode mode;
    QGraphicsLineItem *line;
    SelectorItem *selector;
    MovingView::ViewType viewType;
    QAction *deleteAction;

private:
    void onNewPerceptronAdded(PerceptronInteractorListener *perceptron) override;
    void onNewDataAdded(DataInteractorListener *data) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void updateScene() override;
    void moveSelectedItem(QPointF delta) override;
    void deleteItem(QGraphicsItem *item) override;
    QAction *getDeleteAction() override;
    void clearSelectedItem() override;
    void addArrow();
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
