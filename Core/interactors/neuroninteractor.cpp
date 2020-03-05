#include "neuroninteractor.h"

#include "math.h"

NeuronInteractor::NeuronInteractor()
{

}

double NeuronInteractor::activateFunction(double value) {
    return 1.0 / (1.0 + exp(-value));
}
