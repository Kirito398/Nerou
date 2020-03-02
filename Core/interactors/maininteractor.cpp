#include "maininteractor.h"

MainInteractor::MainInteractor()
{

}

MainInteractor* MainInteractor::getInstance() {
    if (instance == nullptr)
        instance = new MainInteractor();
    return instance;
}

void MainInteractor::run() {
    for (auto sinaps : sinapsModelsList)
        sinaps->init();
}

ModelItem* MainInteractor::addNewItem(MoveItemInterface *listener, ModelItem::ItemType type) {
    ModelItem *newItem;

    switch (type) {
    case ModelItem::Perceptron : {
        newItem = new PerceptronModel(listener);
        break;
    }
    case ModelItem::Convolution : {
        newItem = new PerceptronModel(listener);
        break;
    }
    }

    itemsList.push_back(newItem);
    return newItem;
}

SinapsModel *MainInteractor::makeSinaps(ModelItem *inputItem, ModelItem *outputItem) {
    SinapsModel *sinaps = nullptr;

    if (inputItem->getType() == outputItem->getType() && inputItem->getType() == ModelItem::Perceptron) {
        sinaps = new WeightModel(inputItem, outputItem);
    }

    inputItem->addOutputSinaps(sinaps);
    outputItem->addInputSinaps(sinaps);

    sinapsModelsList.push_back(sinaps);

    return sinaps;
}

void MainInteractor::removeItem(MoveItemInterface *item) {
    for(unsigned long i = 0; i < itemsList.size(); i++) {
        if (itemsList.at(i)->getListener() == item) {
            itemsList.erase(itemsList.begin() + i);
            vector<ModelItem *>(itemsList).swap(itemsList);
            break;
        }
    }
}

void MainInteractor::removeSinaps(SinapsModel *item) {
    for(unsigned long i = 0; i < sinapsModelsList.size(); i++) {
        if (sinapsModelsList.at(i) == item) {
            sinapsModelsList.erase(sinapsModelsList.begin() + i);
            vector<SinapsModel *>(sinapsModelsList).swap(sinapsModelsList);
            break;
        }
    }
}

MainInteractor * MainInteractor::instance;
