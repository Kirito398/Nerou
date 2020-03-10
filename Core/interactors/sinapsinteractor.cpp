#include "sinapsinteractor.h"

#include "iostream"

#include "listeners/SinapsListener.h"

SinapsInteractor::SinapsInteractor(SinapsListener *inputListener, SinapsListener *outputListener, SinapsType type)
{
    this->inputListener = inputListener;
    this->outputListener = outputListener;
    this->type = type;
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

SinapsInteractor::~SinapsInteractor() {

}
