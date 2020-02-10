#include "modelitem.h"

ModelItem::ModelItem(string objectName, MoveItemInterface *listener)
{
    this->objectName = objectName;
    this->listener = listener;
}

void ModelItem::setPosition(float posX, float posY) {
    this->posX = posX;
    this->posY = posY;

    if (listener != nullptr)
        listener->setPosition(posX, posY);
}
