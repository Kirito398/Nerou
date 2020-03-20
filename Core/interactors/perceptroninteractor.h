#ifndef PERCEPTRONINTERACTOR_H
#define PERCEPTRONINTERACTOR_H

#include "interactors/neuroninteractor.h"
#include "listeners/perceptroninteractorlistener.h"

class PerceptronPresentorListener;
class PerceptronModel;

class PerceptronInteractor : public NeuronInteractor, public PerceptronInteractorListener
{
public:
    PerceptronInteractor();
    void onInputSignalChanged() override;
    void setPosition(double x, double y) override;
    PerceptronModel getModel();

private:
    void setView(PerceptronPresentorListener *listener) override;
    void onDeltaValueChanged() override;
    unsigned long getID() override;
    void deleteNeuron() override;
    void clean() override;
    void setOutputNeuron(bool enable) override;
    bool getIsOutputNeuron() override;
    void makeInputSignal();
    void makeInputDelta();
    void calculateOut();
    void calculateDelta();
    void sendSignal();
    void sendDelta();
    void clearInputSignal();
    void clearInputDelta();

private:
    PerceptronPresentorListener *view;
    double *inputSignal;
    double *inputDelta;
    double outValue;
    double deltaValue;
};

#endif // PERCEPTRONINTERACTOR_H
