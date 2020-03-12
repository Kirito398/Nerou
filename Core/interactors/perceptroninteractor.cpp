#include "perceptroninteractor.h"

#include "interfaces/weightinterface.h"
#include "listeners/perceptronpresentorlistener.h"

PerceptronInteractor::PerceptronInteractor()
{
    inputSignal = nullptr;
    inputSignalCount = 0;
    view = nullptr;
}

void PerceptronInteractor::setView(PerceptronPresentorListener *listener) {
    view = listener;

    view->updatePosition(posX, posY);
}

void PerceptronInteractor::setPosition(double x, double y) {
    posX = x;
    posY = y;

    if (view != nullptr)
        view->updatePosition(posX, posY);
}

unsigned long PerceptronInteractor::getID() {
    return id;
}

void PerceptronInteractor::onInputSignalChanged() {
    inputSignalCount++;

    if (inputSignalCount == inputsSinaps.size()) {
        makeInputSignal();
        calculateOut();
        sendSignal();
        clearInputSignal();
    }
}

void PerceptronInteractor::onDeltaValueChanged() {

}

void PerceptronInteractor::makeInputSignal() {
    inputSignal = new double[inputSignalCount];

    for (unsigned long i = 0; i < inputSignalCount; i++) {
        WeightInterface *weight = static_cast<WeightInterface *>(inputsSinaps.at(i));
        inputSignal[i] = weight->getValue();
    }
}

void PerceptronInteractor::calculateOut() {
    double sum = 0;
    for (unsigned long i = 0; i < inputSignalCount; i++)
        sum += inputSignal[i];

    outValue = activateFunction(sum);
}

void PerceptronInteractor::sendSignal() {
    for (unsigned long i = 0; i < outputsSinaps.size(); i++) {
        WeightInterface *weight = static_cast<WeightInterface *>(outputsSinaps.at(i));
        weight->sendSignal(outValue);
    }
}

void PerceptronInteractor::clearInputSignal() {
    delete [] inputSignal;
    inputSignal = nullptr;

    inputSignalCount = 0;
}

void PerceptronInteractor::deleteNeuron() {
    removeNeuron();
}