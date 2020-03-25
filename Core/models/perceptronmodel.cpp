#include "perceptronmodel.h"

PerceptronModel::PerceptronModel()
{
    posX = 0;
    posY = 0;
    id = 0;
    isOutput = false;
    type = -1;
}

double PerceptronModel::getX() {
    return posX;
}

void PerceptronModel::setX(double value) {
    posX = value;
}

double PerceptronModel::getY() {
    return posY;
}

void PerceptronModel::setY(double value) {
    posY = value;
}

unsigned long PerceptronModel::getID() {
    return  id;
}

void PerceptronModel::setID(unsigned long id) {
    this->id = id;
}

bool PerceptronModel::getIsOutput() {
    return isOutput;
}

void PerceptronModel::setIsOutput(bool enable) {
    isOutput = enable;
}

int PerceptronModel::getType() {
    return type;
}

void PerceptronModel::setType(int type) {
    this->type = type;
}
