#include "sinapsmodel.h"

#include <iostream>

SinapsModel::SinapsModel(SinapsListener *inputListener, SinapsListener *outputListener, SinapsType type)
{
    this->inputListener = inputListener;
    this->outputListener = outputListener;
    this->type = type;
}

double SinapsModel::random() {
    return std::rand() % 100 / 100.0 - 0.5;
}

SinapsModel::~SinapsModel() {

}
