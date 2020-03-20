#include "datamodel.h"

#include "models/classmodel.h"

DataModel::DataModel()
{
    posX = 0;
    posY = 0;
    id = 0;
    isOutput = false;
    type = -1;
    isColorMode = false;
}

double DataModel::getX() {
    return posX;
}

void DataModel::setX(double value) {
    posX = value;
}

double DataModel::getY() {
    return posY;
}

void DataModel::setY(double value) {
    posY = value;
}

unsigned long DataModel::getID() {
    return  id;
}

void DataModel::setID(unsigned long id) {
    this->id = id;
}

bool DataModel::getIsOutput() {
    return isOutput;
}

void DataModel::setIsOutput(bool enable) {
    isOutput = enable;
}

int DataModel::getType() {
    return type;
}

void DataModel::setType(int type) {
    this->type = type;
}

bool DataModel::getIsColorMode() {
    return isColorMode;
}

void DataModel::setIsColorMode(bool enable) {
    isColorMode = enable;
}

std::vector<ClassModel> DataModel::getClassList() {
    return classList;
}

void DataModel::setClassList(std::vector<ClassModel> list) {
    //classList.swap(list);
}
