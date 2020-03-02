#include "perceptronmodel.h"

PerceptronModel::PerceptronModel(MoveItemInterface *listener) : ModelItem(listener, Perceptron)
{
    inputSignalCount = 0;
}

void PerceptronModel::onInputSignalChanged() {
    inputSignalCount++;

    if (inputSignalCount == inputItems.size())
        makeInputSignal();
}

void PerceptronModel::makeInputSignal() {
    for (auto weight : inputItems) {

    }
}
