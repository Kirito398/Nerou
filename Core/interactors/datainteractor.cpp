#include "datainteractor.h"

#include "listeners/datapresentorlistener.h"
#include "interfaces/coreinterface.h"
#include "interfaces/weightinterface.h"

DataInteractor::DataInteractor() : NeuronInteractor()
{
    view = nullptr;
}

void DataInteractor::setView(DataPresentorListener *listener) {
    view = listener;
}

void DataInteractor::sendData() {
    dynamic_cast<WeightInterface *>(outputsSinaps.at(0))->sendSignal(1.0);
}

void DataInteractor::onInputSignalChanged() {

}
