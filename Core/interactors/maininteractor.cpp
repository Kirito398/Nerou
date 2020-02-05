#include "maininteractor.h"

MainInteractor::MainInteractor()
{

}

MainInteractor* MainInteractor::getInstance() {
    if (instance == nullptr)
        instance = new MainInteractor();
    return instance;
}

int MainInteractor::addNewItem() {
    int i = itemsList.size();
    itemsList.push_back(ModelItem(to_string(i)));
    return i;
}

MainInteractor * MainInteractor::instance;
