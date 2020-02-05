#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent)
{
    interactor = MainInteractor::getInstance();
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (this->itemAt(event->scenePos(), QTransform()) != nullptr)
        QGraphicsScene::mousePressEvent(event);
    else {
        MoveItem *item = new MoveItem(event->scenePos());
        item->setObjectName(QString("Neuron_").append(QString::number(interactor->addNewItem())));
        //item = this->findChild<MoveItem*>(QString(""), Qt::FindChildrenRecursively);
        this->addItem(item);
    }
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (this->itemAt(event->scenePos(), QTransform()) != nullptr)
        QGraphicsScene::mouseMoveEvent(event);
    else {

    }
}

PaintScene::~PaintScene() {

}
