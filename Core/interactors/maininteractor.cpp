#include "maininteractor.h"

MainInteractor::MainInteractor()
{

}

MainInteractor* MainInteractor::getInstance() {
    if (instance == nullptr)
        instance = new MainInteractor();
    return instance;
}

int MainInteractor::addNewItem(MoveItemInterface *listener) {
    int i = itemsList.size();
    ModelItem newItem = ModelItem(to_string(i), listener);
    currentItem = &newItem;
    itemsList.push_back(newItem);
    return i;
}

void MainInteractor::setCurrentItem(string objectName) {
    for (auto &item : itemsList) {
        if (item.objectName == objectName) {
            currentItem = &item;
            break;
        }
    }
}

void MainInteractor::setItemPosition(float posX, float posY) {
    if (currentItem != nullptr)
        currentItem->setPosition(posX, posY);
}

MainInteractor * MainInteractor::instance;
