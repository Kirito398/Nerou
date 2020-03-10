#ifndef WEIGHTINTERACTOR_H
#define WEIGHTINTERACTOR_H

#include "interfaces/weightinterface.h"
#include "listeners/arrowinteractorlistener.h"

class SinapsPresentorListener;

class WeightInteractor : public WeightInterface, public ArrowInteractorListener
{
public:
    WeightInteractor(SinapsListener *inputListener, SinapsListener *outputListener);
    double getValue() override;
    void sendSignal(double signal) override;
    void init() override;

private:
    double value;
    double weight;
};

#endif // WEIGHTINTERACTOR_H
