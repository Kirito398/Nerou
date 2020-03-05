#include "perceptroninteractor.h"

#include "interactors/weightinteractor.h"
#include "listeners/perceptronpresentorlistener.h"

PerceptronInteractor::PerceptronInteractor()
{
    inputSignal = nullptr;
    inputSignalCount = 0;
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

void PerceptronInteractor::makeInputSignal() {
    inputSignal = new double[inputSignalCount];

    for (unsigned long i = 0; i < inputSignalCount; i++) {
        WeightInteractor *weight = static_cast<WeightInteractor *>(inputsSinaps.at(i));
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
        WeightInteractor *weight = static_cast<WeightInteractor *>(outputsSinaps.at(i));
        weight->sendSignal(outValue);
    }
}

void PerceptronInteractor::clearInputSignal() {
    delete [] inputSignal;
    inputSignal = nullptr;

    inputSignalCount = 0;
}
