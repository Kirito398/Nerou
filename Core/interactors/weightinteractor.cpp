#include "weightinteractor.h"

#include "listeners/sinapspresentorlistener.h"
#include "listeners/SinapsListener.h"
#include "models/weightmodel.h"

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
    grad = 0;
    prevDeltaWeight = 0;
}

WeightModel WeightInteractor::getModel() {
    WeightModel model(id);
    model.setType(type);
    model.setWeight(weight);
    model.setInputNeuronID(inputListener->getID());
    model.setOutputNeuronID(outputListener->getID());

    return model;
}

void WeightInteractor::setWeight(double weight) {
    this->weight = weight;
}

void WeightInteractor::updateSinaps(double learningRange, double alpha) {
    //weight += deltaWeight;

    double deltaWeight = grad * learningRange + alpha * prevDeltaWeight;
    weight += deltaWeight;
    prevDeltaWeight = deltaWeight;
    grad = 0;
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
    //double learningRange = 0.7;
    //double a = 0;
    //deltaWeight += learningRange * grad + a * this->delta;

    double grad = value * delta;
    this->grad += grad;
    this->delta = delta;

    inputListener->onDeltaValueChanged();
}

void WeightInteractor::setView(SinapsPresentorListener *listener) {
    this->view = listener;
}

double WeightInteractor::getValue() {
    return value;
}

double WeightInteractor::getDelta() {
    return delta * weight;
}

void WeightInteractor::deleteSinaps() {
    removeSinaps();
}
