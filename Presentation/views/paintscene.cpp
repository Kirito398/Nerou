#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    interactor = MainInteractor::getInstance();
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() != Qt::LeftButton)
        return;

    switch (mode) {
    case Items:
        if (this->itemAt(event->scenePos(), QTransform()) == nullptr) {
            MoveItem *item = new MoveItem(event->scenePos());
            item->setView(this);
            this->addItem(item);
        }
        break;
    case Arrows:
        line = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
        addItem(line);
        return;
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
    if (line != nullptr && mode == Arrows) {
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
            //add arrow to startitem
            //add arrow to enditem
            addItem(arrow);
            arrow->setZValue(-1000.0);
            arrow->updatePosition();
        }

        removeItem(line);
        delete line;
    }

    line = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
}

void PaintScene::updateScene() {
    this->update();
}

void PaintScene::updateItemSelection() {
    QList <QGraphicsItem *> items = this->items(itemsBoundingRect(), Qt::ContainsItemShape);

    for (auto item : items) {
        MoveItem *selectedItem = dynamic_cast<MoveItem *>(item);
        selectedItem->setSelected(false);
    }
}

void PaintScene::setMode(Mode mode) {
    this->mode = mode;
}
