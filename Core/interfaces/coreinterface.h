#ifndef COREINTERFACE_H
#define COREINTERFACE_H

#include "interactors/sinapsinteractor.h"

class CoreInterface : public SinapsInteractor
{
public:
    CoreInterface(SinapsListener *inputListener, SinapsListener *outputListener);
    virtual double** getValue() = 0;
    virtual void sendSignal(double* signal, unsigned int row, unsigned int column) = 0;
};

#endif // COREINTERFACE_H
