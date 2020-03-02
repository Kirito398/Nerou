#include "sinapsmodel.h"

SinapsModel::SinapsModel(SinapsListener *inputListener, SinapsListener *outputListener)
{
    this->inputListener = inputListener;
    this->outputListener = outputListener;
}

void SinapsModel::setType(SinapsType type) {
    this->type = type;
    init();
}

void SinapsModel::init() {
    if (value != nullptr)
        clearValue();

    switch(type) {
    case Weigth : {
        initWeight();
        break;
    }
    case Core : {
        initCore();
        break;
    }
    }
}

void SinapsModel::initWeight() {
    value = new double(5.0);
}

void SinapsModel::initCore() {
    value = new double[5];
}

void SinapsModel::clearValue() {
    switch(type) {
    case Weigth : {
        delete value;
        break;
    }
    case Core : {
        delete [] value;
        break;
    }
    }

    value = nullptr;
}
