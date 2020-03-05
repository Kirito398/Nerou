#include "weightinteractor.h"

#include "listeners/sinapspresentorlistener.h"

WeightInteractor::WeightInteractor(SinapsListener *inputListener, SinapsListener *outputListener) : SinapsInteractor(inputListener, outputListener, Weigth)
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

double WeightInteractor::getValue() {
    return value;
}
