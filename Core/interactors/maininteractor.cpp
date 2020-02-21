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

MainInteractor * MainInteractor::instance;
