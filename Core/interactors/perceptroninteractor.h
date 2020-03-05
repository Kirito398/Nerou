#ifndef PERCEPTRONINTERACTOR_H
#define PERCEPTRONINTERACTOR_H

#include "interactors/neuroninteractor.h"
#include "listeners/perceptroninteractorlistener.h"

class PerceptronPresenterListener;

class PerceptronInteractor : public NeuronInteractor, public PerceptronInteractorListener
{
public:
    PerceptronInteractor();
    void onInputSignalChanged() override;

private:
    void makeInputSignal();
    void calculateOut();
    void sendSignal();
    void clearInputSignal();

private:
    unsigned long inputSignalCount;
    double *inputSignal;
    double outValue;
};

#endif // PERCEPTRONINTERACTOR_H
