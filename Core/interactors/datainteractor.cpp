#include "datainteractor.h"

#include "listeners/datapresentorlistener.h"
#include "interfaces/coreinterface.h"
#include "interfaces/weightinterface.h"

#include "interfaces/repositoryinterface.h"

DataInteractor::DataInteractor() : NeuronInteractor()
{
    view = nullptr;
    value = nullptr;
    colorValue = nullptr;
    repository = nullptr;
    column = 0;
    row = 0;
    isColorMode = false;
}

void DataInteractor::start(unsigned long classNumber, unsigned long iterationNumber) {
    if (isColorMode) {
        repository->loadValue(listPaths[classNumber][iterationNumber], colorValue);
        colorsToValue();
    } else
        repository->loadValue(listPaths[classNumber][iterationNumber], value);

    sendData();

}

void DataInteractor::sendData() {
    if (outputsSinaps.empty())
        return;

    unsigned int size = column * row * 3;
    unsigned long weightCounter = 0;
    unsigned long coreCounter = 0;

    for (auto sinaps : outputsSinaps) {
        if (sinaps->getType() == sinaps->Weigth) {
            dynamic_cast<WeightInterface *>(sinaps)->sendSignal(value[weightCounter % size]);
            weightCounter++;
            continue;
        }

        CoreInterface *core = dynamic_cast<CoreInterface *>(sinaps);
        core->sendSignal(colorValue[coreCounter % 3], row, column);
        coreCounter++;
    }
}

void DataInteractor::colorsToValue() {
    unsigned int size = column * row;
    value = new double[size * 3];

    unsigned int k = 0;
    for (unsigned int i = 0; i < size; i++) {
        value[k] = red[i];
        k++;
    }

    for (unsigned int i = 0; i < size; i++) {
        value[k] = green[i];
        k++;
    }

    for (unsigned int i = 0; i < size; i++) {
        value[k] = blue[i];
        k++;
    }
}

void DataInteractor::setRepository(RepositoryInterface *repository) {
    this->repository = repository;
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

unsigned long DataInteractor::getID() {
    return id;
}

void DataInteractor::deleteNeuron() {
    removeNeuron();
}

void DataInteractor::onInputSignalChanged() {

}

void DataInteractor::onDeltaValueChanged() {

}
