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

    if (isAnimateTrainingProcessEnabled) {
        view->setOutValue(normalization(value));
        //view->setOutValue(value);
        view->setActive(false);
    }

    sendSignal();
    inputSignalCount = 0;
}

void ConvolutionInteractor::activate() {
    for (unsigned int i = 0; i < value.size(); i++)
        for (unsigned int j = 0; j < value[i].size(); j++)
            value[i][j] = activateFunction(value[i][j]);
}

void ConvolutionInteractor::reActivateDelta() {
    for (unsigned int i = 0; i < value.size(); i++)
        for (unsigned int j = 0; j < value.size(); j++)
            inputDelta[i][j] = inputDelta[i][j] * reActivateFunction(value[i][j]);
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
    model.setActivateFunctionType(activateFunctionType);

    return model;
}

void ConvolutionInteractor::updateFromModel(ConvolutionModel model) {
    id = model.getID();
    posX = model.getX();
    posY = model.getY();
    type = NeuronType(model.getType());
    isActivateFunctionEnabled = model.getIsActivateFunctionEnabled();
    activateFunctionType = ActivateFunctionType(model.getActivateFunctionType());
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
    if (isActivateFunctionEnabled) reActivateDelta();
    sendDelta();
    inputDeltaCount = 0;
}

unsigned long ConvolutionInteractor::getID() {
    return id;
}

void ConvolutionInteractor::getInputSignal() {
    if (isAnimateTrainingProcessEnabled)
        view->setActive(true);

    value.clear();
    CoreInterface *sinaps = static_cast<CoreInterface *>(inputsSinaps.at(0));
    value = sinaps->getValue();
}

void ConvolutionInteractor::makeInputDelta() {
    this->inputDelta.clear();

    if (outputsSinaps.at(0)->getType() == outputsSinaps.at(0)->Core) {
        std::vector<std::vector<double>> inputDelta = static_cast<CoreInterface *>(outputsSinaps.at(0))->getDelta();

        for (auto deltas : inputDelta)
            this->inputDelta.push_back(std::vector<double>(deltas.size()));

        for (auto sinaps : outputsSinaps) {
            inputDelta = static_cast<CoreInterface *>(sinaps)->getDelta();

            for (unsigned int i = 0; i < inputDelta.size(); i++)
                for (unsigned int j = 0; j < inputDelta[i].size(); j++)
                    this->inputDelta[i][j] += inputDelta[i][j];
        }

        return;
    }

    double temp[inputDeltaCount];
    for (unsigned int i = 0; i < inputDeltaCount; i++)
        temp[i] = 0;

    for (unsigned long i = 0; i < inputDeltaCount; i++) {
        WeightInterface *weight = static_cast<WeightInterface *>(outputsSinaps.at(i));
        temp [i] = weight->getDelta();
    }

    for (unsigned int i = 0; i < value.size(); i++) {
        this->inputDelta.push_back(std::vector<double>());
        for (unsigned int j = 0; j < value[i].size(); j++) {
            if (i * value[i].size() >= inputDeltaCount)
                this->inputDelta[i].push_back(0);
            else
                this->inputDelta[i].push_back(temp[i * value[i].size() + j]);
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

void ConvolutionInteractor::setActivateFunctionType(int type) {
    activateFunctionType = ActivateFunctionType(type);
}

int ConvolutionInteractor::getActivateFunctionType() {
    return activateFunctionType;
}

void ConvolutionInteractor::setCoreSize(int size) {
    for (auto sinaps : inputsSinaps)
        dynamic_cast<CoreInterface *>(sinaps)->setCoreSize(size);
}

int ConvolutionInteractor::getCoreSize() {
    if (inputsSinaps.empty())
        return 0;

    return dynamic_cast<CoreInterface *>(inputsSinaps.at(0))->getCoreSize();
}

void ConvolutionInteractor::setPoolCoreSize(int size) {
    for (auto sinaps : inputsSinaps)
        dynamic_cast<CoreInterface *>(sinaps)->setPoolCoreSize(size);
}

int ConvolutionInteractor::getPoolCoreSize() {
    if (inputsSinaps.empty())
        return 0;

    return dynamic_cast<CoreInterface *>(inputsSinaps.at(0))->getPoolCoreSize();
}

void ConvolutionInteractor::deleteNeuron() {
    removeNeuron();
}

void ConvolutionInteractor::clean() {
    value.clear();
    inputDelta.clear();
    view->setOutValue(value);
}
