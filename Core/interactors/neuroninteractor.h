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
    void setID(unsigned long id);
    unsigned long getID();

protected:
    double activateFunction(double value);

protected:
    std::vector<SinapsInteractor *> inputsSinaps;
    std::vector<SinapsInteractor *> outputsSinaps;

private:
    unsigned long id;
};

#endif // NEURONINTERACTOR_H
