#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsLineItem>

#include <models/moveitem.h>
#include <models/perceptronitem.h>
#include <models/convolutionitem.h>
#include <interactors/maininteractor.h>
#include <interfaces/PaintSceneInterface.h>
#include <models/arrowitem.h>
#include <models/selectoritem.h>
#include <models/dataitem.h>
#include "listeners/mainpresentorlistener.h"

class PaintScene : public QGraphicsScene, public PaintSceneInterface, public MainPresentorListener
{
public:
    PaintScene(QObject *parent = nullptr);
    enum Mode {Selector, Items, Arrows};
    void setMode(Mode mode);
    //void setItemType(ModelItem::ItemType type);
    //ModelItem::ItemType getItemType();

private:
    MainInteractor* interactor;
    ArrowItem* currentArrow;
    Mode mode;
    QGraphicsLineItem *line;
    SelectorItem *selector;
    //ModelItem::ItemType itemType;

private:
    void onNewPerceptronCreated(PerceptronInteractorListener *perceptron) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void updateScene() override;
    void moveSelectedItem(QPointF delta) override;
    void addArrowItem();
    void addMoveItem(QPointF position);
    void onItemsModePress(QGraphicsSceneMouseEvent *event);
    void onArrowsModePress(QGraphicsSceneMouseEvent *event);
    void onSelectorModePress(QGraphicsSceneMouseEvent *event);
    void onItemsModeMove(QGraphicsSceneMouseEvent *event);
    void onArrowsModeMove(QGraphicsSceneMouseEvent *event);
    void onSelectorModeMove(QGraphicsSceneMouseEvent *event);
    void onItemsModeRelease(QGraphicsSceneMouseEvent *event);
    void onArrowsModeRelease(QGraphicsSceneMouseEvent *event);
    void onSelectorModeRelease(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTSCENE_H
