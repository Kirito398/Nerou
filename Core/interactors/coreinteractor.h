#ifndef COREINTERACTOR_H
#define COREINTERACTOR_H

#include "interfaces/coreinterface.h"
#include "listeners/arrowinteractorlistener.h"

class SinapsPresentorListener;
class CoreModel;

class CoreInteractor : public CoreInterface, public ArrowInteractorListener
{
public:
    CoreInteractor(SinapsListener *inputListener, SinapsListener *outputListener);
    CoreModel getModel();
    void updateFromModel(CoreModel model);

private:
    void init() override;
    void updateSinaps(double learningRange, double alpha) override;
    void sendSignal(std::vector<std::vector<double>> signal) override;
    std::vector<std::vector<double>> getValue() override;
    void deleteSinaps() override;
    void setView(SinapsPresentorListener *listener) override;
    std::vector<std::vector<double>> getDelta() override;
    void sendDelta(std::vector<std::vector<double>> delta) override;
    void validConvolution(std::vector<std::vector<double>> signal);
    void revConvolution(std::vector<std::vector<double>> delta);
    void maxPooling();
    std::vector<std::vector<double>> maxPoolingRev(std::vector<std::vector<double>> delta);
    std::vector<std::vector<double>> convolution(std::vector<std::vector<double> > input, std::vector<std::vector<double> > core);
    std::vector<std::vector<double>> rotate180(std::vector<std::vector<double>> input);

private:
    SinapsPresentorListener *view;
    unsigned int coreSize, maxPoolingCoreSize;
    std::vector<std::vector<double>> value;
    std::vector<std::vector<double>> weight;
    std::vector<std::vector<double>> delta;
    std::vector<std::vector<bool>> maxValue;
    std::vector<std::vector<double>> inputSignal;
    std::vector<std::vector<double>> grad;
    bool isMaxPoolingEnabled;
};

#endif // COREINTERACTOR_H
