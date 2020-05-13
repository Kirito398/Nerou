#ifndef WEIGHTINTERFACE_H
#define WEIGHTINTERFACE_H

#include "interactors/sinapsinteractor.h"

class WeightInterface : public SinapsInteractor
{
public:
    WeightInterface(SinapsListener *inputListener, SinapsListener *outputListener) : SinapsInteractor(inputListener, outputListener, Weigth) {}
    virtual double getValue() = 0;
    virtual double getDelta() = 0;
    virtual void sendSignal(double signal) = 0;
    virtual void sendDelta(double delta) = 0;
};

#endif // WEIGHTINTERFACE_H
