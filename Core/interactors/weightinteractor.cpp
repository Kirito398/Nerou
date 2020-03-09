#include "weightinteractor.h"

#include "listeners/sinapspresentorlistener.h"
#include "listeners/SinapsListener.h"

WeightInteractor::WeightInteractor(SinapsListener *inputListener, SinapsListener *outputListener) : WeightInterface(inputListener, outputListener)
{
    init();
}

void WeightInteractor::init() {
    weight = random();
    value = 0;
}

void WeightInteractor::sendSignal(double signal) {
    value = signal * weight;
    outputListener->onInputSignalChanged();
}

void WeightInteractor::sendSignal(double **signal) {
    value = signal[0][0] * weight;
    outputListener->onInputSignalChanged();
}

double WeightInteractor::getValue() {
    return value;
}
