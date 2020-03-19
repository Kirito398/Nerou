#include "weightinteractor.h"

#include "listeners/sinapspresentorlistener.h"
#include "listeners/SinapsListener.h"

WeightInteractor::WeightInteractor(SinapsListener *inputListener, SinapsListener *outputListener) : WeightInterface(inputListener, outputListener)
{
    view = nullptr;

    init();
}

void WeightInteractor::init() {
    if (inputListener->getType() == NeuronType::Data || outputListener->getType() == NeuronType::Data)
        weight = 1.0;
    else
        weight = random();
    value = 0;
    delta = 0;
    sumDelta = 0;
}

void WeightInteractor::updateSinaps() {
    weight += sumDelta;
    sumDelta = 0;
}

void WeightInteractor::sendSignal(double signal) {
    if (view != nullptr)
        view->setActive(true);

    value = signal * weight;
    outputListener->onInputSignalChanged();

    if (view != nullptr)
        view->setActive(false);
}

void WeightInteractor::sendDelta(double delta) {
    this->delta = delta;
    sumDelta += delta;
    inputListener->onDeltaValueChanged();
}

void WeightInteractor::setView(SinapsPresentorListener *listener) {
    this->view = listener;
}

double WeightInteractor::getValue() {
    return value;
}

double WeightInteractor::getDelta() {
    return delta;
}

void WeightInteractor::deleteSinaps() {
    removeSinaps();
}
