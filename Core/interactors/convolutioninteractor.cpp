#include "convolutioninteractor.h"

#include "listeners/convolutionpresentorlistener.h"
#include "models/convolutionmodel.h"
#include "interfaces/coreinterface.h"
#include "interfaces/weightinterface.h"

ConvolutionInteractor::ConvolutionInteractor() : NeuronInteractor(Convolution)
{
    view = nullptr;
    inputSignalCount = 0;
    inputDeltaCount = 0;
    isActivateFunctionEnabled = true;
}

void ConvolutionInteractor::onInputSignalChanged() {
    inputSignalCount++;

    if (inputSignalCount != inputsSinaps.size())
        return;

    getInputSignal();
    if (isActivateFunctionEnabled) activate();
    sendSignal();
    inputSignalCount = 0;
}

void ConvolutionInteractor::activate() {
    for (unsigned int i = 0; i < value.size(); i++)
        for (unsigned int j = 0; j < value[i].size(); j++)
            value[i][j] = activateFunction(value[i][j]);
}

void ConvolutionInteractor::setPosition(double x, double y) {
    posX = x;
    posY = y;

    if (view != nullptr)
        view->updatePosition(posX, posY);
}

ConvolutionModel ConvolutionInteractor::getModel() {
    ConvolutionModel model(id);

    model.setX(posX);
    model.setY(posY);
    model.setType(type);
    model.setIsActivateFunctionEnabled(isActivateFunctionEnabled);

    return model;
}

void ConvolutionInteractor::updateFromModel(ConvolutionModel model) {
    id = model.getID();
    posX = model.getX();
    posY = model.getY();
    //type = NeuronType(model.getType());
    isActivateFunctionEnabled = model.getIsActivateFunctionEnabled();
}

void ConvolutionInteractor::setView(ConvolutionPresentorListener *listener) {
    view = listener;
    view->updatePosition(posX, posY);
}

void ConvolutionInteractor::onDeltaValueChanged() {
    inputDeltaCount++;

    if (inputDeltaCount != outputsSinaps.size())
        return;

    makeInputDelta();
    sendDelta();
    inputDeltaCount = 0;
}

unsigned long ConvolutionInteractor::getID() {
    return id;
}

void ConvolutionInteractor::getInputSignal() {
    view->setActive(true);

    value.clear();
    CoreInterface *sinaps = static_cast<CoreInterface *>(inputsSinaps.at(0));
    value = sinaps->getValue();

    view->setOutValue(value);
    view->setActive(false);
}

void ConvolutionInteractor::makeInputDelta() {
    if (outputsSinaps.at(0)->getType() == outputsSinaps.at(0)->Core) {
        inputDelta = static_cast<CoreInterface *>(outputsSinaps.at(0))->getDelta();
        return;
    }

    inputDelta.clear();
    double temp[inputDeltaCount];

    for (unsigned int i = 0; i < inputDeltaCount; i++)
        temp[i] = 0;

    for (unsigned long i = 0; i < inputDeltaCount; i++) {
        WeightInterface *weight = static_cast<WeightInterface *>(outputsSinaps.at(i));
        temp [i] = weight->getDelta();
    }

    for (unsigned int i = 0; i < value.size(); i++) {
        inputDelta.push_back(std::vector<double>());
        for (unsigned int j = 0; j < value[i].size(); j++) {
            if (i * value[i].size() >= inputDeltaCount)
                inputDelta[i].push_back(0);
            else
                inputDelta[i].push_back(temp[i * value[i].size()]);
        }
    }
}

void ConvolutionInteractor::sendSignal() {
    unsigned int size = value.size() * value[0].size();
    unsigned long weightCounter = 0;

    double temp[size];
    for (unsigned int i = 0; i < value.size(); i++)
        for (unsigned int j = 0; j < value[i].size(); j++)
            temp[i * value[i].size() + j] = value[i][j];

    for (auto sinaps : outputsSinaps) {
        if (sinaps->getType() == sinaps->Weigth) {
            static_cast<WeightInterface *>(sinaps)->sendSignal(temp[weightCounter++ % size]);
            continue;
        }

        CoreInterface *core = static_cast<CoreInterface *>(sinaps);
        core->sendSignal(value);
    }
}

void ConvolutionInteractor::sendDelta() {
    for (auto sinaps : inputsSinaps)
        static_cast<CoreInterface *>(sinaps)->sendDelta(inputDelta);
}

void ConvolutionInteractor::deleteNeuron() {
    removeNeuron();
}

void ConvolutionInteractor::clean() {
    value.clear();
    inputDelta.clear();
    view->setOutValue(value);
}
