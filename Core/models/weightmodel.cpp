#include "weightmodel.h"

WeightModel::WeightModel(SinapsListener *inputListener, SinapsListener *outputListener) : SinapsModel(inputListener, outputListener, SinapsType::Weigth)
{
    init();
}

void WeightModel::init() {
    weight = random();
    value = 0;
}

void WeightModel::sendSignal(double signal) {
    value = signal * weight;
    outputListener->onInputSignalChanged();
}

double WeightModel::getValue() {
    return value;
}
