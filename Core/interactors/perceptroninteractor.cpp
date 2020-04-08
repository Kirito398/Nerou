#include "perceptroninteractor.h"

#include "interfaces/weightinterface.h"
#include "listeners/perceptronpresentorlistener.h"
#include "models/perceptronmodel.h"

PerceptronInteractor::PerceptronInteractor() : NeuronInteractor(Perceptron)
{
    inputSignal = nullptr;
    inputDelta = nullptr;
    inputSignalCount = 0;
    inputDeltaCount = 0;
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
        view->setActive(true);
        makeInputSignal();
        calculateOut();
        sendSignal();
        clearInputSignal();
        view->setActive(false);
    }
}

void PerceptronInteractor::onDeltaValueChanged() {
    inputDeltaCount++;

    if (inputDeltaCount == outputsSinaps.size()) {
        makeInputDelta();
        calculateDelta();
        sendDelta();
        clearInputDelta();
    }
}

void PerceptronInteractor::setOutputNeuron(bool enable) {
    isOutputNeuronEnable(enable);
}

bool PerceptronInteractor::getIsOutputNeuron() {
    return isOutputNeuron();
}

void PerceptronInteractor::makeInputSignal() {
    inputSignal = new double[inputSignalCount];

    for (unsigned long i = 0; i < inputSignalCount; i++) {
        WeightInterface *weight = static_cast<WeightInterface *>(inputsSinaps.at(i));
        inputSignal[i] = weight->getValue();
    }
}

void PerceptronInteractor::makeInputDelta() {
    inputDelta = new double[inputDeltaCount];

    for (unsigned long i = 0; i < inputDeltaCount; i++) {
        WeightInterface *weight = static_cast<WeightInterface *>(outputsSinaps.at(i));
        inputDelta[i] = weight->getDelta();
    }
}

void PerceptronInteractor::calculateOut() {
    double sum = 0;
    for (unsigned long i = 0; i < inputSignalCount; i++)
        sum += inputSignal[i];

    outValue = activateFunction(sum);

    view->setOutValue(outValue);
}

void PerceptronInteractor::calculateDelta() {
//    if (inputsSinaps.size() == 1 && inputsSinaps[0]->getOutputNeuron()->getType() == Data) {
//        deltaValue = inputDelta[0];
//        return;
//    }

    double sum  = 0;
    for (unsigned long i = 0; i < inputDeltaCount; i++)
        sum += inputDelta[i];

    deltaValue = sum * reActivateFunction(outValue);
}

void PerceptronInteractor::sendSignal() {
    for (unsigned long i = 0; i < outputsSinaps.size(); i++) {
        WeightInterface *weight = static_cast<WeightInterface *>(outputsSinaps.at(i));
        weight->sendSignal(outValue);
    }
}

void PerceptronInteractor::sendDelta() {
    for (unsigned long i = 0; i < inputsSinaps.size(); i++) {
        WeightInterface * weight = static_cast<WeightInterface *>(inputsSinaps.at(i));
        weight->sendDelta(deltaValue);
    }
}

void PerceptronInteractor::clearInputSignal() {
    delete [] inputSignal;
    inputSignal = nullptr;

    inputSignalCount = 0;
}

void PerceptronInteractor::clearInputDelta() {
    delete [] inputDelta;
    inputDelta = nullptr;

    inputDeltaCount = 0;
}

PerceptronModel PerceptronInteractor::getModel() {
    PerceptronModel model;

    model.setX(posX);
    model.setY(posY);
    model.setID(id);
    model.setType(type);
    model.setIsOutput(isOutput);

    return model;
}

void PerceptronInteractor::updateFromModel(PerceptronModel model) {
    posX = model.getX();
    posY = model.getY();
    id = model.getID();
    //type = NeuronType(model.getType());
    isOutput =  model.getIsOutput();
}

void PerceptronInteractor::clean() {
    clearInputSignal();
    view->setOutValue(0);
}

void PerceptronInteractor::deleteNeuron() {
    removeNeuron();
}
