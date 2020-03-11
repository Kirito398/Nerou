#include "perceptronpresentor.h"

#include "listeners/perceptroninteractorlistener.h"
#include "listeners/perceptronviewlistener.h"

PerceptronPresentor::PerceptronPresentor()
{
    interactor = nullptr;
}

void PerceptronPresentor::setView(PerceptronViewListener *listener) {
    view = listener;
}

void PerceptronPresentor::setInteractor(PerceptronInteractorListener *listener) {
    interactor = listener;
    interactor->setView(this);
}

void PerceptronPresentor::updatePosition(double x, double y) {
    view->updatePosition(x, y);
}

void PerceptronPresentor::setPosition(double x, double y) {
    interactor->setPosition(x, y);
}

unsigned long PerceptronPresentor::getID() {
    return interactor->getID();
}

PerceptronPresentor::~PerceptronPresentor() {
    if (interactor != nullptr)
        interactor->deleteNeuron();
}
