#include "sinapsinteractor.h"

#include <iostream>

#include "interfaces/maininteractorinterface.h"
#include "listeners/SinapsListener.h"

SinapsInteractor::SinapsInteractor(SinapsListener *inputListener, SinapsListener *outputListener, SinapsType type)
{
    this->inputListener = inputListener;
    this->outputListener = outputListener;
    this->type = type;
    id = 0;
}

double SinapsInteractor::random() {
    return std::rand() % 100 / 100.0 - 0.5;
}

SinapsInteractor::SinapsType SinapsInteractor::getType() {
    return type;
}

SinapsListener *SinapsInteractor::getInputNeuron() {
    return inputListener;
}

SinapsListener *SinapsInteractor::getOutputNeuron() {
    return outputListener;
}

void SinapsInteractor::setInteractor(MainInteractorInterface *interface) {
    interactor = interface;
}

void SinapsInteractor::removeSinaps() {
    interactor->removeSinaps(id);
}

void SinapsInteractor::setID(unsigned long id) {
    this->id = id;
}

unsigned long SinapsInteractor::getID() const {
    return id;
}

SinapsInteractor::~SinapsInteractor() {
    inputListener->removeSinaps(id);
    outputListener->removeSinaps(id);
}
