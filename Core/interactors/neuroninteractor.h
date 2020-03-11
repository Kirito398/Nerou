#ifndef NEURONINTERACTOR_H
#define NEURONINTERACTOR_H

#include <vector>

#include "listeners/SinapsListener.h"

class SinapsInteractor;
class MainInteractorInterface;

class NeuronInteractor : public SinapsListener
{
public:
    enum NeuronType {Perceptron, Convolution, Data};
    enum FunctionType {Sin};

public:
    NeuronInteractor();
    virtual ~NeuronInteractor();
    void setID(unsigned long id);
    unsigned long getID();
    bool addArrow(SinapsInteractor* arrow);
    void setInteractor(MainInteractorInterface *interface);

protected:
    double activateFunction(double value);
    void removeNeuron();

private:
    bool isArrowAlreadyAdded(SinapsInteractor* arrow);
    void removeSinapses();
    void removeSinaps(unsigned long sinapsID) override;

protected:
    std::vector<SinapsInteractor *> inputsSinaps;
    std::vector<SinapsInteractor *> outputsSinaps;
    double posX, posY;
    unsigned long id;

private:
    MainInteractorInterface *interactor;
};

#endif // NEURONINTERACTOR_H
