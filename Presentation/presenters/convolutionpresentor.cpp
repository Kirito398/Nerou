#include "convolutionpresentor.h"

#include "listeners/convolutioninteractorlistener.h"
#include "listeners/convolutionviewlistener.h"

ConvolutionPresentor::ConvolutionPresentor()
{
    interactor = nullptr;
    view = nullptr;
}

void ConvolutionPresentor::setView(ConvolutionViewListener *listener) {
    view = listener;
}

void ConvolutionPresentor::setInteractor(ConvolutionInteractorListener *listener) {
    interactor = listener;
    interactor->setView(this);
}

void ConvolutionPresentor::setPosition(double x, double y) {
    interactor->setPosition(x, y);
}

unsigned long ConvolutionPresentor::getID() {
    return interactor->getID();
}

void ConvolutionPresentor::updatePosition(double x, double y) {
    view->updatePosition(x, y);
}

void ConvolutionPresentor::setActive(bool enable) {
    view->setActive(enable);
}

ConvolutionPresentor::~ConvolutionPresentor() {
    if (interactor != nullptr)
        interactor->deleteNeuron();
}
