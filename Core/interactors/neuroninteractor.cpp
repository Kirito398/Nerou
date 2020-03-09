#include "neuroninteractor.h"

#include "math.h"

NeuronInteractor::NeuronInteractor()
{
    id = 0;
}

double NeuronInteractor::activateFunction(double value) {
    return 1.0 / (1.0 + exp(-value));
}

void NeuronInteractor::setID(unsigned long id) {
    this->id = id;
}

unsigned long NeuronInteractor::getID() {
    return id;
}
