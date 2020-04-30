#include "tabledatainteractor.h"

#include "listeners/tabledatapresentorlistener.h"

TableDataInteractor::TableDataInteractor() : NeuronInteractor(Data)
{
    view = nullptr;
    repository = nullptr;
    lossFunctionType = CrossEntropy;
}

void TableDataInteractor::removeSinaps(unsigned long sinapsID) {
    NeuronInteractor::removeSinaps(sinapsID);
}

void TableDataInteractor::clean() {

}

void TableDataInteractor::setView(TableDataPresentorListener *listener) {
    view = listener;
    view->updatePosition(posX, posY);
}

void TableDataInteractor::setPosition(double x, double y) {
    posX = x;
    posY = y;

    if (view != nullptr)
        view->updatePosition(posX, posY);
}

void TableDataInteractor::deleteNeuron() {
    removeNeuron();
}

unsigned long TableDataInteractor::getID() {
    return id;
}

void TableDataInteractor::setLossFunctionType(LossFunctionType type) {
    lossFunctionType = type;
}

LossFunctionType TableDataInteractor::getLossFunctionType() {
    return lossFunctionType;
}

void TableDataInteractor::setActivateFunctionType(int type) {
    activateFunctionType = ActivateFunctionType(type);
}

int TableDataInteractor::getActivateFunctiontype() {
    return activateFunctionType;
}
