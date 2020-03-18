#include "perceptronpresentor.h"

#include "listeners/perceptroninteractorlistener.h"
#include "listeners/perceptronviewlistener.h"

#include <QString>
#include <iostream>

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

void PerceptronPresentor::setOutputNeuron(bool enable) {
    interactor->setOutputNeuron(enable);
}

void PerceptronPresentor::setActive(bool enable) {
    view->setActive(enable);
}

void PerceptronPresentor::setOutValue(double value) {
    view->setOutValue(QString::fromStdString(std::to_string(value)));
}

PerceptronPresentor::~PerceptronPresentor() {
    if (interactor != nullptr)
        interactor->deleteNeuron();
}
