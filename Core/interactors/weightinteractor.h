#ifndef WEIGHTINTERACTOR_H
#define WEIGHTINTERACTOR_H

#include "interfaces/weightinterface.h"
#include "listeners/arrowinteractorlistener.h"

class SinapsPresentorListener;
class WeightModel;

class WeightInteractor : public WeightInterface, public ArrowInteractorListener
{
public:
    WeightInteractor(SinapsListener *inputListener, SinapsListener *outputListener);
    double getValue() override;
    double getDelta() override;
    void sendSignal(double signal) override;
    void init() override;
    void updateSinaps(double learningRange, double alpha) override;
    WeightModel getModel();
    void setWeight(double weight);

private:
    void sendDelta(double delta) override;
    void deleteSinaps() override;
    void setView(SinapsPresentorListener *listener) override;

private:
    SinapsPresentorListener *view;
    double value;
    double input;
    double weight;
    double delta;
    double grad;
    double prevDeltaWeight;
};

#endif // WEIGHTINTERACTOR_H
