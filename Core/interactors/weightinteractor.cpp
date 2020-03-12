#include "weightinteractor.h"

#include "listeners/sinapspresentorlistener.h"
#include "listeners/SinapsListener.h"

WeightInteractor::WeightInteractor(SinapsListener *inputListener, SinapsListener *outputListener) : WeightInterface(inputListener, outputListener)
{
    view = nullptr;

    init();
}

void WeightInteractor::init() {
    weight = inputListener->getType() == NeuronType::Data ? 1.0 : random();
    value = 0;
}

void WeightInteractor::sendSignal(double signal) {
    view->setActive(true);

    value = signal * weight;
    outputListener->onInputSignalChanged();

    view->setActive(false);
}

void WeightInteractor::setView(SinapsPresentorListener *listener) {
    this->view = listener;
}

double WeightInteractor::getValue() {
    return value;
}

void WeightInteractor::deleteSinaps() {
    removeSinaps();
}
