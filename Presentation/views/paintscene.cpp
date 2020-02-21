#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    interactor = MainInteractor::getInstance();
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    updateItemSelection();

    if (this->itemAt(event->scenePos(), QTransform()) != nullptr)
        QGraphicsScene::mousePressEvent(event);
    else {
        MoveItem *item = new MoveItem(event->scenePos());
        item->setView(this);
        this->addItem(item);
    }
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (this->itemAt(event->scenePos(), QTransform()) != nullptr)
        QGraphicsScene::mouseMoveEvent(event);
    else {

    }
}

void PaintScene::onInputCircleClicked(QPointF position) {
    //TODO end making arrow
}

void PaintScene::onOutputCircleClicked(QPointF position) {
    //TODO start making arrow
}

void PaintScene::updateItemSelection() {
    QList <QGraphicsItem *> items = this->items(itemsBoundingRect(), Qt::ContainsItemShape);

    for (auto item : items) {
        MoveItem *selectedItem = dynamic_cast<MoveItem *>(item);
        selectedItem->setSelected(false);
    }
}

PaintScene::~PaintScene() {

}
