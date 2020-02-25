#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    interactor = MainInteractor::getInstance();
    line = nullptr;
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() != Qt::LeftButton)
        return;

    this->clearSelection();

    switch (mode) {
    case Items:
        onItemsModeClicked(event);
        break;
    case Arrows:
        onArrowsModeClicked(event);
        break;
    }

    QGraphicsScene::mousePressEvent(event);
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (mode == Arrows && line != nullptr) {
        QLineF newLine(line->line().p1(), event->scenePos());
        line->setLine(newLine);
    } else if (mode == Items) QGraphicsScene::mouseMoveEvent(event);
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (line != nullptr && mode == Arrows)
        addArrowItem();

    line = nullptr;

    if (mode == Items)
        QGraphicsScene::mouseReleaseEvent(event);
}

void PaintScene::updateScene() {
    this->update();
}

void PaintScene::setMode(Mode mode) {
    this->mode = mode;
}

void PaintScene::addArrowItem() {
    QList<QGraphicsItem *> startItems = items(line->line().p1());
    if (startItems.count() && startItems.first() == line)
        startItems.removeFirst();

    QList<QGraphicsItem *> endItems = items(line->line().p2());
    if (endItems.count() && endItems.first() == line)
        endItems.removeFirst();

    if (startItems.count() && endItems.count() && startItems.first() != endItems.first()) {
        MoveItem *startItem = qgraphicsitem_cast<MoveItem *>(startItems.first());
        MoveItem *endItem = qgraphicsitem_cast<MoveItem *>(endItems.first());
        ArrowItem *arrow = new ArrowItem(startItem, endItem);

        if (startItem->addArrow(arrow) && endItem->addArrow(arrow)) {
            addItem(arrow);
            arrow->setZValue(-1000.0);
            arrow->updatePosition();
        }
    }

    removeItem(line);
    delete line;
}

void PaintScene::addMoveItem(QPointF position) {
    MoveItem *newItem = new MoveItem(position);
    newItem->setView(this);
    newItem->setSelected(true);
    this->addItem(newItem);
}

void PaintScene::onItemsModeClicked(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem *item =  this->itemAt(event->scenePos(), QTransform());
    if (item == nullptr)
        addMoveItem(event->scenePos());
    else
        item->setSelected(true);
}

void PaintScene::onArrowsModeClicked(QGraphicsSceneMouseEvent *event) {
    line = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
    addItem(line);
}
