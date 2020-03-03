#include "modelitem.h"

#include "interfaces/moveiteminterface.h"

ModelItem::ModelItem(MoveItemInterface *listener, ItemType type)
{
    this->listener = listener;
    this->type = type;
}

void ModelItem::setPosition(double posX, double posY) {
    this->posX = posX;
    this->posY = posY;

    if (listener != nullptr)
        listener->setPosition(this->posX, this->posY);
}

void ModelItem::addInputSinaps(SinapsModel* inputItem) {
    inputItems.push_back(inputItem);
}

void ModelItem::addOutputSinaps(SinapsModel* outputItem) {
    outputItems.push_back(outputItem);
}

void ModelItem::removeInputSinaps(SinapsModel* inputItem) {
    for (unsigned long i = 0; i < inputItems.size(); i++) {
        if (inputItems.at(i) == inputItem) {
            inputItems.erase(inputItems.begin() + i);
            vector<SinapsModel *>(inputItems).swap(inputItems);
            break;
        }
    }
}

void ModelItem::removeOutputSinaps(SinapsModel *outputItem) {
    for (unsigned long i = 0; i < outputItems.size(); i++) {
        if (outputItems.at(i) == outputItem) {
            outputItems.erase(outputItems.begin() + i);
            vector<SinapsModel *>(outputItems).swap(outputItems);
            break;
        }
    }
}

double ModelItem::activateFunction(double value) {
    return 1.0 / (1.0 + exp(-value));
}

MoveItemInterface *ModelItem::getListener() {
    return listener;
}

ModelItem::ItemType ModelItem::getType() {
    return type;
}
