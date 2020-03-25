#include "convolutioninteractor.h"

#include "listeners/convolutionpresentorlistener.h"
#include "models/convolutionmodel.h"
#include "interfaces/coreinterface.h"
#include "interfaces/weightinterface.h"

ConvolutionInteractor::ConvolutionInteractor() : NeuronInteractor(Convolution)
{
    view = nullptr;
    value = nullptr;
    currentRow = 0;
    currentColumn = 0;
    inputSignalCount = 0;
    inputDeltaCount = 0;
    isActivateFunctionEnabled = true;
}

void ConvolutionInteractor::onInputSignalChanged() {
    inputSignalCount++;

    if (inputSignalCount != inputsSinaps.size())
        return;

    getInputSignal();
    if (isActivateFunctionEnabled) activateFunction(value, currentRow * currentColumn);
    sendSignal();
    deleteValue();
    inputSignalCount = 0;
}

void ConvolutionInteractor::setPosition(double x, double y) {
    posX = x;
    posY = y;

    if (view != nullptr)
        view->updatePosition(posX, posY);
}

ConvolutionModel ConvolutionInteractor::getModel() {
    ConvolutionModel model(id);

    return model;
}

void ConvolutionInteractor::updateFromModel(ConvolutionModel model) {
    id = model.getID();
}

void ConvolutionInteractor::setView(ConvolutionPresentorListener *listener) {
    view = listener;
    view->updatePosition(posX, posY);
}

void ConvolutionInteractor::onDeltaValueChanged() {

}

unsigned long ConvolutionInteractor::getID() {
    return id;
}

void ConvolutionInteractor::getInputSignal() {
    view->setActive(true);
    if (value != nullptr)
        deleteValue();

    CoreInterface *sinaps = static_cast<CoreInterface *>(inputsSinaps.at(0));
    value = sinaps->getValue();
    currentRow = sinaps->getRow();
    currentColumn = sinaps->getColumn();

    view->setOutValue(value, currentRow, currentColumn);
    view->setActive(false);
}

void ConvolutionInteractor::sendSignal() {
    unsigned int size = currentRow * currentColumn;
    unsigned long weightCounter = 0;

    for (auto sinaps : outputsSinaps) {
        if (sinaps->getType() == sinaps->Weigth) {
            dynamic_cast<WeightInterface *>(sinaps)->sendSignal(value[weightCounter++ % size]);
            continue;
        }

        CoreInterface *core = dynamic_cast<CoreInterface *>(sinaps);
        core->sendSignal(value, currentRow, currentColumn);
    }
}

void ConvolutionInteractor::deleteValue() {
    if (value == nullptr)
        return;

    delete [] value;
    value = nullptr;
}

void ConvolutionInteractor::deleteNeuron() {
    removeNeuron();
}

void ConvolutionInteractor::clean() {
    //clearInputSignal();
    //view->setOutValue();
}
