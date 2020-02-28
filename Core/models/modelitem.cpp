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

void ModelItem::removeInputItem(ModelItem* inputItem) {
    for (unsigned long i = 0; i < inputItems.size(); i++) {
        if (inputItems.at(i) == inputItem) {
            inputItems.erase(inputItems.begin() + i);
            vector<ModelItem *>(inputItems).swap(inputItems);
            break;
        }
    }
}

void ModelItem::removeOutputItem(ModelItem* outputItem) {
    for (unsigned long i = 0; i < outputItems.size(); i++) {
        if (outputItems.at(i) == outputItem) {
            outputItems.erase(outputItems.begin() + i);
            vector<ModelItem *>(outputItems).swap(outputItems);
            break;
        }
    }
}
