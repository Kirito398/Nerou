#include "convolutionmodel.h"

ConvolutionModel::ConvolutionModel(unsigned long id)
{
    this->id = id;
}

unsigned long ConvolutionModel::getID() {
    return id;
}
