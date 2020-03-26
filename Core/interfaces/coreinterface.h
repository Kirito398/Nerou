#ifndef COREINTERFACE_H
#define COREINTERFACE_H

#include "interactors/sinapsinteractor.h"

class CoreInterface : public SinapsInteractor
{
public:
    CoreInterface(SinapsListener *inputListener, SinapsListener *outputListener) : SinapsInteractor(inputListener, outputListener, Core) {}
    virtual double* getValue() = 0;
    virtual unsigned int getRow() = 0;
    virtual unsigned int getColumn() = 0;
    virtual void sendSignal(double* signal, unsigned int row, unsigned int column) = 0;
    virtual double *getDelta() = 0;
    virtual void sendDelta(double *delta) = 0;
};

#endif // COREINTERFACE_H
