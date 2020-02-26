#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsLineItem>

#include <models/moveitem.h>
#include <interactors/maininteractor.h>
#include <interfaces/PaintSceneInterface.h>
#include <models/arrowitem.h>
#include <models/selectoritem.h>

class PaintScene : public QGraphicsScene, public PaintSceneInterface
{
public:
    PaintScene(QObject *parent = nullptr);
    enum Mode {Selector, Items, Arrows};
    void setMode(Mode mode);

private:
    MainInteractor* interactor;
    ArrowItem* currentArrow;
    Mode mode;
    QGraphicsLineItem *line;
    SelectorItem *selector;

private:
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
