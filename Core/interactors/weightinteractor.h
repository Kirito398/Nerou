#ifndef WEIGHTINTERACTOR_H
#define WEIGHTINTERACTOR_H

#include "interactors/sinapsinteractor.h"

class SinapsPresentorListener;

class WeightInteractor : public SinapsInteractor
{
public:
    WeightInteractor(SinapsListener *inputListener, SinapsListener *outputListener);
    double getValue();
    void sendSignal(double signal);
    void init() override;

private:
    double value;
    double weight;
};

#endif // WEIGHTINTERACTOR_H
