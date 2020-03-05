#ifndef NEURONINTERACTOR_H
#define NEURONINTERACTOR_H

#include <vector>

#include "listeners/SinapsListener.h"

class SinapsInteractor;

class NeuronInteractor : public SinapsListener
{
public:
    enum NeuronType {Perceptron, Convolution, Data};
    enum FunctionType {Sin};

public:
    NeuronInteractor();

protected:
    double activateFunction(double value);

protected:
    std::vector<SinapsInteractor *> inputsSinaps;
    std::vector<SinapsInteractor *> outputsSinaps;

};

#endif // NEURONINTERACTOR_H
