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
    void addArrowItem();
    void addMoveItem(QPointF position);
    void onItemsModeClicked(QGraphicsSceneMouseEvent *event);
    void onArrowsModeClicked(QGraphicsSceneMouseEvent *event);
    void onSelectorModeClicked(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTSCENE_H
