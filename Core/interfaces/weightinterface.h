#ifndef WEIGHTINTERFACE_H
#define WEIGHTINTERFACE_H

#include "interactors/sinapsinteractor.h"

class WeightInterface : public SinapsInteractor
{
public:
    WeightInterface(SinapsListener *inputListener, SinapsListener *outputListener);
    virtual double getValue() = 0;
    virtual void sendSignal(double signal) = 0;
};

#endif // WEIGHTINTERFACE_H
