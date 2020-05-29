#include "sinapsinteractor.h"

#include <iostream>
#include <math.h>

#include "interfaces/maininteractorinterface.h"
#include "listeners/SinapsListener.h"

SinapsInteractor::SinapsInteractor(SinapsListener *inputListener, SinapsListener *outputListener, SinapsType type)
{
    this->inputListener = inputListener;
    this->outputListener = outputListener;
    this->type = type;
    id = 0;
    iterationNumber = 0;
}

double SinapsInteractor::random() {
    return std::rand() % 100 / 100.0 - 0.5;
}

double SinapsInteractor::optimize(double grad, double learningRange, double alpha, double prevDelta, double b, double &prevS) {
    //return rmsProp(grad, learningRange, alpha, prevDelta, b, prevS);
    //return gradient(grad, learningRange);
    return momentum(grad, learningRange, alpha, prevDelta);
}

double SinapsInteractor::gradient(double grad, double learningRange) {
    return -grad * learningRange;
}

double SinapsInteractor::momentum(double grad, double learningRange, double alpha, double prevDelta) {
    return -grad * learningRange + alpha * prevDelta;
}

double SinapsInteractor::rmsProp(double grad, double learningRange, double alpha, double prevDelta, double b, double &prevS) {
    double s = b * prevS + (1.0 - b) * pow(grad, 2.0);
    prevS = s;
    return momentum(grad, learningRange / sqrt(s + 0.00000001), alpha, prevDelta);
}

double SinapsInteractor::adam(double grad, double learningRange, double alpha, double prevDelta, double b, double &prevS) {
    iterationNumber++;

    double s = (b * prevS + (1.0 - b) * pow(grad, 2.0)) / (1.0 - b);
    double v = momentum(grad, learningRange, alpha, prevDelta) / (1.0 - alpha);

    prevS = s;

    return learningRange * v / sqrt(s + 0.00000001);
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
