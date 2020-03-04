#include "maininteractor.h"

MainInteractor::MainInteractor()
{
    itemFactory = ItemFactory();
    sinapsFactory = SinapsFactory();
}

MainInteractor* MainInteractor::getInstance() {
    if (instance == nullptr)
        instance = new MainInteractor();
    return instance;
}

void MainInteractor::run() {
    for (auto sinaps : sinapsModelsList)
        sinaps->init();

    ModelItem *data = itemFactory.create(nullptr, ModelItem::VectorData);
    SinapsModel *sinaps = sinapsFactory.create(data, itemsList[0], SinapsModel::Weigth);
    data->addOutputSinaps(sinaps);
    itemsList[0]->addInputSinaps(sinaps);
    sinaps->init();

    dynamic_cast<DataModel *>(data)->sendData();
}

ModelItem* MainInteractor::addNewItem(MoveItemInterface *listener, ModelItem::ItemType type) {
    ModelItem *newItem = itemFactory.create(listener, type);
    itemsList.push_back(newItem);
    return newItem;
}

SinapsModel *MainInteractor::makeSinaps(ModelItem *inputItem, ModelItem *outputItem) {
    SinapsModel::SinapsType type;

    if (inputItem->getType() == outputItem->getType() && inputItem->getType() == ModelItem::Perceptron) {
        type = SinapsModel::Weigth;
    } else {
        type = SinapsModel::Core;
    }

    SinapsModel *sinaps = sinapsFactory.create(inputItem, outputItem, type);

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
