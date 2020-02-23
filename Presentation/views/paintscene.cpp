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
        if (mode == Arrows) {
            line = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
            addItem(line);
            return;
        }
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
    if (line != nullptr && mode == Arrows) {
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
