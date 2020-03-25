#include "convolutioninteractor.h"

#include "listeners/convolutionpresentorlistener.h"
#include "models/convolutionmodel.h"

ConvolutionInteractor::ConvolutionInteractor() : NeuronInteractor(Convolution)
{
    view = nullptr;
    inputSignalCount = 0;
    inputDeltaCount = 0;
}

void ConvolutionInteractor::onInputSignalChanged() {

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

void ConvolutionInteractor::deleteNeuron() {
    removeNeuron();
}

void ConvolutionInteractor::clean() {
    //clearInputSignal();
    //view->setOutValue();
}
