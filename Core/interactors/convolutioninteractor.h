#ifndef CONVOLUTIONINTERACTOR_H
#define CONVOLUTIONINTERACTOR_H

#include "interactors/neuroninteractor.h"
#include "listeners/convolutioninteractorlistener.h"

class ConvolutionPresentorListener;
class ConvolutionModel;

class ConvolutionInteractor : public NeuronInteractor, public ConvolutionInteractorListener
{
public:
    ConvolutionInteractor();
    void onInputSignalChanged() override;
    void setPosition(double x, double y) override;
    ConvolutionModel getModel();
    void updateFromModel(ConvolutionModel model);

private:
    void setView(ConvolutionPresentorListener *listener) override;
    void onDeltaValueChanged() override;
    unsigned long getID() override;
    void deleteNeuron() override;
    void clean() override;
    void getInputSignal();
    void sendSignal();
    void deleteValue();
    void makeInputDelta();
    void sendDelta();
    void deleteDelta();

private:
    ConvolutionPresentorListener *view;
    double *value, *inputDelta;
    unsigned int currentRow, currentColumn;
    bool isActivateFunctionEnabled;
};

#endif // CONVOLUTIONINTERACTOR_H
