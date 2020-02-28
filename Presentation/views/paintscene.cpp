#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    interactor = MainInteractor::getInstance();
    line = nullptr;
    selector = nullptr;
    mode = PaintScene::Selector;
}

void PaintScene::moveSelectedItem(QPointF delta) {
    QList<QGraphicsItem *> selectedItems = this->selectedItems();

    for (auto item : selectedItems) {
        MoveItem *moveItem = dynamic_cast<MoveItem *>(item);
        if (moveItem != nullptr)
            moveItem->setPosition(item->pos() + delta);
    }
}

void PaintScene::onItemsModePress(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem *item =  this->itemAt(event->scenePos(), QTransform());
    if (item == nullptr)
        addMoveItem(event->scenePos());
    else
        item->setSelected(true);
}

void PaintScene::onArrowsModePress(QGraphicsSceneMouseEvent *event) {
    line = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
    addItem(line);
}

void PaintScene::onSelectorModePress(QGraphicsSceneMouseEvent *event) {
    QGraphicsItem *item =  this->itemAt(event->scenePos(), QTransform());
    if (item == nullptr) {
        selector = new SelectorItem(event->scenePos());
        selector->setView(this);
        addItem(selector);
    } else {
        if (!item->isSelected()) {
            this->clearSelection();
            item->setSelected(true);
        }
    }
}

void PaintScene::onItemsModeMove(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseMoveEvent(event);
}

void PaintScene::onArrowsModeMove(QGraphicsSceneMouseEvent *event) {
    if (line == nullptr)
        return;

    QLineF newLine(line->line().p1(), event->scenePos());
    line->setLine(newLine);
}

void PaintScene::onSelectorModeMove(QGraphicsSceneMouseEvent *event) {
    if (selector != nullptr)
        selector->setEndPoint(event->scenePos());

    QGraphicsScene::mouseMoveEvent(event);
}

void PaintScene::onItemsModeRelease(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
}

void PaintScene::onArrowsModeRelease(QGraphicsSceneMouseEvent *event) {
    if (line == nullptr)
        return;

    addArrowItem();

    Q_UNUSED(event)
}

void PaintScene::onSelectorModeRelease(QGraphicsSceneMouseEvent *event) {
    if (selector == nullptr)
        return;

    QList<QGraphicsItem *> selectedItems = items(selector->boundingRect());

    for (auto item : selectedItems)
        item->setSelected(true);

    removeItem(selector);
    delete selector;

    Q_UNUSED(event)
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
            this->clearSelection();
            arrow->setSelected(true);
            arrow->setZValue(-1000.0);
            arrow->updatePosition();
            addItem(arrow);
        }
    }

    removeItem(line);
    delete line;
}

void PaintScene::addMoveItem(QPointF position) {
    MoveItem *newItem = new PerceptronItem(position);
    newItem->setView(this);
    newItem->setSelected(true);
    this->addItem(newItem);
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() != Qt::LeftButton)
        return;

    if (mode != Selector)
        this->clearSelection();

    switch (mode) {
    case Selector:
        onSelectorModePress(event);
        break;
    case Items:
        onItemsModePress(event);
        break;
    case Arrows:
        onArrowsModePress(event);
        break;
    }

    QGraphicsScene::mousePressEvent(event);
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    switch (mode) {
    case Selector:
        onSelectorModeMove(event);
        break;
    case Arrows:
        onArrowsModeMove(event);
        break;
    case Items:
        onItemsModeMove(event);
        break;
    }
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    switch (mode) {
    case Selector:
        onSelectorModeRelease(event);
        break;
    case Arrows:
        onArrowsModeRelease(event);
        break;
    case Items:
        onItemsModeRelease(event);
        break;
    }

    selector = nullptr;
    line = nullptr;
}

void PaintScene::updateScene() {
    this->update();
}
