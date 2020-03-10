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
    bool addArrow(SinapsInteractor* arrow);

protected:
    double activateFunction(double value);

private:
    bool isArrowAlreadyAdded(SinapsInteractor* arrow);

protected:
    std::vector<SinapsInteractor *> inputsSinaps;
    std::vector<SinapsInteractor *> outputsSinaps;
    double posX, posY;
    unsigned long id;
};

#endif // NEURONINTERACTOR_H
