#include "datainteractor.h"

#include "interactors/weightinteractor.h"
#include "listeners/datapresentorlistener.h"

DataInteractor::DataInteractor() : NeuronInteractor()
{

}

void DataInteractor::sendData() {
    dynamic_cast<WeightInteractor *>(outputsSinaps.at(0))->sendSignal(1.0);
}

void DataInteractor::onInputSignalChanged() {

}
