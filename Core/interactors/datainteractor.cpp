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
}



void DataInteractor::start(unsigned long classNumber, unsigned long iterationNumber) {
    repository->loadValue(listPaths[classNumber][iterationNumber], value, &row, &column);
}

void DataInteractor::setRepository(RepositoryInterface *repository) {
    this->repository = repository;
}

void DataInteractor::onValueLoaded(double *value, unsigned int row, unsigned int column) {
    if (this->value != nullptr) {
        delete [](this->value);
        this->value = nullptr;
    }

    this->value = value;
    this->row = row;
    this->column = column;

    sendData();
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

void DataInteractor::onInputSignalChanged() {

}

void DataInteractor::onDeltaValueChanged() {

}
