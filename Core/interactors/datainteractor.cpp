#include "datainteractor.h"

#include "listeners/datapresentorlistener.h"
#include "interfaces/coreinterface.h"
#include "interfaces/weightinterface.h"

#include "interfaces/repositoryinterface.h"

DataInteractor::DataInteractor() : NeuronInteractor()
{
    view = nullptr;
    value = nullptr;
    repository = nullptr;
    column = 0;
    row = 0;
}

void DataInteractor::setView(DataPresentorListener *listener) {
    view = listener;

    view->updatePosition(posX, posY);
}

void DataInteractor::setPosition(double x, double y) {
    posX = x;
    posY = y;

    if (view != nullptr)
        view->updatePosition(posX, posY);
}

void DataInteractor::start(unsigned long classNumber, unsigned long iterationNumber) {
    repository->loadValue(listPaths[classNumber][iterationNumber], value, &row, &column);
}

void DataInteractor::setRepository(RepositoryInterface *repository) {
    this->repository = repository;
}

void DataInteractor::sendData() {
    if (outputsSinaps.empty())
        return;

    if (outputsSinaps.at(0)->getType() == outputsSinaps.at(0)->Weigth) {
        for (unsigned long i = 0; i < outputsSinaps.size(); i++)
            dynamic_cast<WeightInterface *>(outputsSinaps.at(i))->sendSignal(value[i]);
        return;
    }

    if (outputsSinaps.at(0)->getType() == outputsSinaps.at(0)->Core) {
        for (auto sinaps : outputsSinaps)
            dynamic_cast<CoreInterface *>(sinaps)->sendSignal(value, row, column);
        return;
    }
}

unsigned long DataInteractor::getID() {
    return id;
}

void DataInteractor::onInputSignalChanged() {

}

void DataInteractor::onDeltaValueChanged() {

}
