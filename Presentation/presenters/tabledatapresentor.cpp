#include "tabledatapresentor.h"

#include "listeners/tabledataviewlistener.h"

TableDataPresentor::TableDataPresentor()
{
    interactor = nullptr;
    view = nullptr;
}

void TableDataPresentor::setView(TableDataViewListener *listener) {
    view = listener;
}

void TableDataPresentor::setInteractor(TableDataInteractorListener *listener) {
    interactor = listener;
    interactor->setView(this);
}

void TableDataPresentor::setPosition(double x, double y) {
    interactor->setPosition(x, y);
}

unsigned long TableDataPresentor::getID() {
    return interactor->getID();
}

void TableDataPresentor::setActivateFunctionType(int type) {
    interactor->setActivateFunctionType(type);
}

int TableDataPresentor::getActivateFunctionType() {
    return interactor->getActivateFunctiontype();
}

void TableDataPresentor::setLossFunctionType(LossFunctionType type) {
    interactor->setLossFunctionType(type);
}

LossFunctionType TableDataPresentor::getLossFunctionType() {
    return interactor->getLossFunctionType();
}

void TableDataPresentor::updatePosition(double x, double y) {
    view->updatePosition(x, y);
}

TableDataPresentor::~TableDataPresentor() {
    if (interactor != nullptr)
        interactor->deleteNeuron();;
}
