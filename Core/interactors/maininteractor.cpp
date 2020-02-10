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
    itemsList.push_back(ModelItem(to_string(i), listener));
    return i;
}

void MainInteractor::setItemPosition(float posX, float posY, string objectName) {
    int id = stoi(objectName);
    for (int i = 0; i < itemsList.size(); i++) {
        if (itemsList[i].objectName == objectName) {
            itemsList[i].setPosition(posX, posY);
            break;
        }
    }
    //itemsList[id].setPosition(posX, posY);
}

MainInteractor * MainInteractor::instance;
