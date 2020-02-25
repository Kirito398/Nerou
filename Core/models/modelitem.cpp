#include "modelitem.h"

ModelItem::ModelItem(MoveItemInterface *listener)
{
    this->listener = listener;
}

void ModelItem::setPosition(double posX, double posY) {
    this->posX = posX;
    this->posY = posY;

    if (listener != nullptr)
        listener->setPosition(this->posX, this->posY);
}

void ModelItem::addInputItem(ModelItem* inputItem) {
    inputItems.push_back(inputItem);
}

void ModelItem::addOutputItem(ModelItem* outputItem) {
    outputItems.push_back(outputItem);
}
