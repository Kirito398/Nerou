#include "sinapsmodel.h"

SinapsModel::SinapsModel(SinapsListener *inputListener, SinapsListener *outputListener)
{
    this->inputListener = inputListener;
    this->outputListener = outputListener;
}
