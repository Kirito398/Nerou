#include "maininteractor.h"

MainInteractor::MainInteractor()
{

}

MainInteractor* MainInteractor::getInstance() {
    if (instance == nullptr)
        instance = new MainInteractor();
    return instance;
}

ModelItem* MainInteractor::addNewItem(MoveItemInterface *listener) {
    ModelItem *newItem = new ModelItem(listener);
    itemsList.push_back(*newItem);
    return newItem;
}

void MainInteractor::removeItem(MoveItemInterface *item) {
    for(unsigned long i = 0; i < itemsList.size(); i++) {
        if (itemsList.at(i).getListener() == item) {
            itemsList.erase(itemsList.begin() + i);
            vector<ModelItem>(itemsList).swap(itemsList);
            break;
        }
    }
}

MainInteractor * MainInteractor::instance;
