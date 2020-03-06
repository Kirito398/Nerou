#ifndef PERCEPTRONINTERACTOR_H
#define PERCEPTRONINTERACTOR_H

#include "interactors/neuroninteractor.h"
#include "listeners/perceptroninteractorlistener.h"

class PerceptronPresentorListener;

class PerceptronInteractor : public NeuronInteractor, public PerceptronInteractorListener
{
public:
    PerceptronInteractor();
    void onInputSignalChanged() override;

private:
    void setView(PerceptronPresentorListener *listener) override;
    void makeInputSignal();
    void calculateOut();
    void sendSignal();
    void clearInputSignal();

private:
    PerceptronPresentorListener *view;
    unsigned long inputSignalCount;
    double *inputSignal;
    double outValue;
};

#endif // PERCEPTRONINTERACTOR_H
