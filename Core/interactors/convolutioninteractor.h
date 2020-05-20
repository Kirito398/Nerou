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
    void setActivateFunctionType(int type) override;
    int getActivateFunctionType() override;
    void setCoreSize(int size) override;
    int getCoreSize() override;
    void setPoolCoreSize(int size) override;
    int getPoolCoreSize() override;
    void activate();
    void reActivateDelta();
    void getInputSignal();
    void sendSignal();
    void makeInputDelta();
    void sendDelta();

private:
    ConvolutionPresentorListener *view;
    std::vector<std::vector<double>> value, inputDelta;
    bool isActivateFunctionEnabled;
};

#endif // CONVOLUTIONINTERACTOR_H
