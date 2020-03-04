#include "perceptronmodel.h"

#include "models/weightmodel.h"

PerceptronModel::PerceptronModel(MoveItemInterface *listener) : ModelItem(listener, Perceptron)
{
    inputSignal = nullptr;
    inputSignalCount = 0;
}

void PerceptronModel::onInputSignalChanged() {
    inputSignalCount++;

    if (inputSignalCount == inputItems.size()) {
        makeInputSignal();
        calculateOut();
        sendSignal();
        clearInputSignal();
    }
}

void PerceptronModel::makeInputSignal() {
    inputSignal = new double[inputSignalCount];

    for (unsigned long i = 0; i < inputSignalCount; i++) {
        WeightModel *weight = static_cast<WeightModel *>(inputItems.at(i));
        inputSignal[i] = weight->getValue();
    }
}

void PerceptronModel::calculateOut() {
    double sum = 0;
    for (unsigned long i = 0; i < inputSignalCount; i++)
        sum += inputSignal[i];

    outValue = activateFunction(sum);
}

void PerceptronModel::sendSignal() {
    for (unsigned long i = 0; i < outputItems.size(); i++) {
        WeightModel *weight = static_cast<WeightModel *>(outputItems.at(i));
        weight->sendSignal(outValue);
    }
}

void PerceptronModel::clearInputSignal() {
    delete [] inputSignal;
    inputSignal = nullptr;

    inputSignalCount = 0;
}
