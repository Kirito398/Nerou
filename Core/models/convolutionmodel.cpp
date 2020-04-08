#include "convolutionmodel.h"

ConvolutionModel::ConvolutionModel(unsigned long id)
{
    this->id = id;
}

unsigned long ConvolutionModel::getID() {
    return id;
}

double ConvolutionModel::getX() {
    return posX;
}

void ConvolutionModel::setX(double value) {
    posX = value;
}

double ConvolutionModel::getY() {
    return posY;
}

void ConvolutionModel::setY(double value) {
    posY = value;
}

void ConvolutionModel::setID(unsigned long id) {
    this->id = id;
}

bool ConvolutionModel::getIsActivateFunctionEnabled() {
    return isActivateFunctionEnabled;
}

void ConvolutionModel::setIsActivateFunctionEnabled(bool enable) {
    isActivateFunctionEnabled = enable;
}

int ConvolutionModel::getType() {
    return type;
}

void ConvolutionModel::setType(int type) {
    this->type = type;
}
