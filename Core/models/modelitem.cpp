#include "modelitem.h"

ModelItem::ModelItem(MoveItemInterface *listener)
{
    this->listener = listener;
}

void ModelItem::setPosition(float posX, float posY) {
    this->posX = posX;
    this->posY = posY;

    if (listener != nullptr)
        listener->setPosition(this->posX, this->posY);
}
