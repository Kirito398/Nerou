#include "coremodel.h"

CoreModel::CoreModel(unsigned long id)
{
    this->id = id;
    type = -1;
    inputNeuronID = -1;
    outputNeuronID = -1;
    coreSize = 0;
    maxPoolingCoreSize = 0;
    isMaxPoolingEnabled = false;
}

unsigned long CoreModel::getID() {
    return id;
}

void CoreModel::setType(int type) {
    this->type = type;
}

int CoreModel::getType() {
    return type;
}

void CoreModel::setInputNeuronID(unsigned long id) {
    inputNeuronID = id;
}

unsigned long CoreModel::getInputNeuronID() {
    return inputNeuronID;
}

void CoreModel::setOutputNeuronID(unsigned long id) {
    outputNeuronID = id;
}

unsigned long CoreModel::getOutputNeuronID() {
    return outputNeuronID;
}

void CoreModel::setWeight(std::vector<std::vector<double>> weight) {
    this->weight = weight;
}

std::vector<std::vector<double>> CoreModel::getWeight() {
    return weight;
}

void CoreModel::setCoreSize(unsigned long size) {
    coreSize = size;
}

unsigned long CoreModel::getCoreSize() {
    return coreSize;
}

void CoreModel::setMaxPoolingCoreSize(unsigned long size) {
    maxPoolingCoreSize = size;
}

unsigned long CoreModel::getMaxPoolingCoreSize() {
    return maxPoolingCoreSize;
}

void CoreModel::setIsMaxPoolingEnable(bool enable) {
    isMaxPoolingEnabled = enable;
}

bool CoreModel::getIsMaxPoolingEnable() {
    return isMaxPoolingEnabled;
}
