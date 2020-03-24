#include "weightmodel.h"

WeightModel::WeightModel(unsigned long id)
{
    this->id = id;
    type = -1;
    inputNeuronID = -1;
    outputNeuronID = -1;
    weight = 0;
}

unsigned long WeightModel::getID() {
    return id;
}

void WeightModel::setType(int type) {
    this->type = type;
}

int WeightModel::getType() {
    return type;
}

void WeightModel::setInputNeuronID(unsigned long id) {
    inputNeuronID = id;
}

unsigned long WeightModel::getInputNeuronID() {
    return inputNeuronID;
}

void WeightModel::setOutputNeuronID(unsigned long id) {
    outputNeuronID = id;
}

unsigned long WeightModel::getOutputNeuronID() {
    return outputNeuronID;
}

void WeightModel::setWeight(double weight) {
    this->weight = weight;
}

double WeightModel::getWeight() {
    return weight;
}
