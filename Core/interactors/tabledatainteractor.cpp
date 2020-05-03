#include "tabledatainteractor.h"

#include "listeners/tabledatapresentorlistener.h"
#include "interfaces/repositoryinterface.h"
#include "models/tabledatasetmodel.h"

TableDataInteractor::TableDataInteractor() : NeuronInteractor(Data)
{
    view = nullptr;
    repository = nullptr;
    activateFunctionType = Sigmoid;
    lossFunctionType = CrossEntropy;
    dataSet = new TableDataSetModel();
}

std::vector<std::vector<std::string>> TableDataInteractor::loadTableValue(std::string path) {
    return repository->loadTableValue(path);
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

void TableDataInteractor::setRepository(RepositoryInterface *repository) {
    this->repository = repository;
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

void TableDataInteractor::onInputSignalChanged() {

}

void TableDataInteractor::onDeltaValueChanged() {

}
