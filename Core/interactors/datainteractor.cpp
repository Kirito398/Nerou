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
    classNumber = 0;
    iterationNumber = 0;
    isColorMode = false;
}

void DataInteractor::start(unsigned long classNumber, unsigned long iterationNumber) {
    if (iterationNumber > listPaths[classNumber].size())
        return;

    view->setImage(listPaths[classNumber][iterationNumber]);

//    if (isColorMode) {
//        repository->loadValue(listPaths[classNumber][iterationNumber], colorValue);
//        colorsToValue();
//    } else
//        repository->loadValue(listPaths[classNumber][iterationNumber], value);

//    sendData();
}

void DataInteractor::sendData() {
    if (outputsSinaps.empty())
        return;

    unsigned int size = isColorMode ? column * row * 3 : column * row;
    unsigned long weightCounter = 0;
    unsigned long coreCounter = 0;

    for (auto sinaps : outputsSinaps) {
        if (sinaps->getType() == sinaps->Weigth) {
            dynamic_cast<WeightInterface *>(sinaps)->sendSignal(value[weightCounter++ % size]);
            continue;
        }

        CoreInterface *core = dynamic_cast<CoreInterface *>(sinaps);

        if (isColorMode)
            core->sendSignal(colorValue[coreCounter++ % 3], row, column);
        else
            core->sendSignal(value, row, column);
    }
}

void DataInteractor::colorsToValue() {
    unsigned int size = column * row;
    value = new double[size * 3];

    for (unsigned int i = 0; i < 3; i++) {
        for (unsigned int j = 0; j < size; j++) {
            value[i*size+j] = colorValue[i][j];
        }
    }
}

void DataInteractor::addClass(std::vector<std::string> list) {
    listPaths.push_back(list);
    classNumber++;

    if (list.size() > iterationNumber)
        iterationNumber = list.size();
}

void DataInteractor::setRepository(RepositoryInterface *repository) {
    this->repository = repository;
}

unsigned long DataInteractor::getClassNumber() {
    return classNumber;
}

unsigned long DataInteractor::getIterationNumber() {
    return iterationNumber;
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