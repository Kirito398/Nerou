#include "datainteractor.h"

#include "listeners/datapresentorlistener.h"
#include "interfaces/coreinterface.h"
#include "interfaces/weightinterface.h"
#include "interfaces/repositoryinterface.h"
#include "models/classmodel.h"

DataInteractor::DataInteractor() : NeuronInteractor(Data)
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
    if (classList.empty())
        return;

    if (iterationNumber > classList[classNumber].getTrainingPathsList().size())
        return;

    view->setImage(classList[classNumber].getTrainingPathsList()[iterationNumber]);

    if (isColorMode) {
        colorValue = repository->loadColorValue(classList[classNumber].getTrainingPathsList()[iterationNumber]);
        normalization(colorValue, 3, row * column);
        colorsToValue();
    } else {
        value = repository->loadValue(classList[classNumber].getTrainingPathsList()[iterationNumber]);
        normalization(value, row * column);
    }

    sendData();
    clearColorValue();
    clearValue();
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

void DataInteractor::addClass(ClassModel model) {
    classList.push_back(model);

    makeLearningSinaps(model.getNeuronID(), id);
}

ClassModel DataInteractor::getClass(unsigned long id) {
    return classList[id];
}

void DataInteractor::clearClassList() {
    classList.clear();

    for(auto sinaps : inputsSinaps)
        sinaps->removeSinaps();
}

void DataInteractor::setRepository(RepositoryInterface *repository) {
    this->repository = repository;
}

unsigned long DataInteractor::getClassNumber() {
    return classList.size();
}

unsigned long DataInteractor::getTrainingIterationNumber() {
    unsigned long number = 0;

    for (auto item : classList) {
        unsigned long size = item.getTrainingPathsList().size();

        if (size > number)
            number = size;
    }

    return number;
}

void DataInteractor::clearColorValue() {
    if (colorValue == nullptr)
        return;

    for (unsigned int i = 0; i < 3; i++)
        delete [](colorValue[i]);
    delete [](colorValue);

    colorValue = nullptr;
}

void DataInteractor::clearValue() {
    if (value == nullptr)
        return;

    delete [](value);
    value = nullptr;
}

void DataInteractor::setSize(unsigned long row, unsigned long column) {
    this->row = row;
    this->column = column;
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

void DataInteractor::removeSinaps(unsigned long sinapsID) {
    for (auto sinaps : inputsSinaps) {
        if (sinaps->getID() != sinapsID)
            continue;

        unsigned long neuronID = sinaps->getInputNeuron()->getID();

        for (unsigned long i = 0; i < classList.size(); i++) {
            ClassModel model = classList.at(i);
            if (model.getNeuronID() != neuronID)
                continue;

            classList.erase(classList.begin() + i);
            std::vector<ClassModel>(classList).swap(classList);
            break;
        }
    }

    NeuronInteractor::removeSinaps(sinapsID);
}

void DataInteractor::deleteNeuron() {
    removeNeuron();
}

void DataInteractor::clean() {
    clearValue();
    clearColorValue();
    view->setImage("");
}

RepositoryInterface *DataInteractor::getRepository() {
    return repository;
}

void DataInteractor::onInputSignalChanged() {

}

void DataInteractor::onDeltaValueChanged() {

}
